import "DPI-C" function void ebreak_call();

module EbreakCall(
    input clock,
    input reset,
    input isEbreak,
);
    initial begin
        if (isEbreak) begin
            ebreak_call();
        end
    end
endmodule