import "DPI-C" function void ebreak_call();

module EbreakCall(
    input clock,
    input reset,
    input isEbreak
);
    initial begin
        $display("Before calling C Method");
        ebreak_call();
        $display("After calling C Method");
    end
endmodule