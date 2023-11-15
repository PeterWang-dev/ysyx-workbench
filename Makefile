STUID = ysyx_23060000
STUNAME = 王嘉宸

# DO NOT modify the following code!!!

TRACER = tracer-ysyx
GITFLAGS = -q --author='$(TRACER) <tracer@ysyx.org>' --no-verify --allow-empty

YSYX_HOME = $(NEMU_HOME)/..
WORK_BRANCH = $(shell git rev-parse --abbrev-ref HEAD | tr '/' '-') # replace slash in branch
# WORK_INDEX = $(YSYX_HOME)/.git/index.$(WORK_BRANCH)
GIT_DIR = $(shell cat $(YSYX_HOME)/.git | cut -c 9- )
WORK_INDEX = $(YSYX_HOME)/$(GIT_DIR)/index.$(WORK_BRANCH) # point to submodule .git dir
TRACER_BRANCH = $(TRACER)

# LOCK_DIR = $(YSYX_HOME)/.git/
LOCK_DIR = $(YSYX_HOME)/$(GIT_DIR)/ # point to submodule .git dir

# prototype: git_soft_checkout(branch)
define git_soft_checkout
	git checkout --detach -q && git reset --soft $(1) -q -- && git checkout $(1) -q --
endef

# prototype: git_commit(msg)
define git_commit
	-@flock $(LOCK_DIR) $(MAKE) -C $(YSYX_HOME) .git_commit MSG='$(1)'
	-@sync
endef

.git_commit:
	-@while (test -e $(GIT_DIR)/index.lock); do sleep 0.1; done;               `# wait for other git instances`
	-@git branch $(TRACER_BRANCH) -q 2>/dev/null || true                 `# create tracer branch if not existent`
	-@cp -a $(GIT_DIR)/index $(WORK_INDEX)                                     `# backup git index`
	-@$(call git_soft_checkout, $(TRACER_BRANCH))                        `# switch to tracer branch`
	-@git add . -A --ignore-errors                                       `# add files to commit`
	-@(echo "> $(MSG)" && echo $(STUID) $(STUNAME) && uname -a && uptime `# generate commit msg`) \
	                | git commit -F - $(GITFLAGS)                        `# commit changes in tracer branch`
	-@$(call git_soft_checkout, $(WORK_BRANCH))                          `# switch to work branch`
	-@mv $(WORK_INDEX) $(GIT_DIR)/index                                        `# restore git index`

.clean_index:
	rm -f $(WORK_INDEX)

_default:
	@echo "Please run 'make' under subprojects."

.PHONY: .git_commit .clean_index _default
