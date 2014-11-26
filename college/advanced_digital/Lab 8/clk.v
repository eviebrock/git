module clk (
iclk,     // input clock
oclk     // output clock
);
input iclk;  // input
output reg oclk; // output
reg [1:24] halfcount = 24'b0;
parameter halfcountmax = 24'd13500000;
reg clkstate = 1'b0;
always @(posedge iclk) begin
	if (halfcount == halfcountmax) begin
		halfcount <= 24'b0;
		clkstate <= ~clkstate;
	end
	else halfcount <= halfcount + 24'b1;
	
	oclk <= clkstate;
end
endmodule