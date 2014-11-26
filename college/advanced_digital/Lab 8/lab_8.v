module lab_8 (
L,     // left
R,     // right
H,     // hazard
clockdiv,    // clock
Lights // lights
);
input L, R, H, clockdiv; // inputs
output reg [1:6] Lights; // outputs

wire clock;

clk myclock (.iclk(clockdiv), .oclk(clock));

parameter IDLE = 3'b000, LA = 3'b001, LB = 3'b010, LC = 3'b011, RA = 3'b100, RB = 3'b101, RC = 3'b110, LR = 3'b111;
reg [2:0]	y;

always @(posedge clock) begin
case(y)
IDLE : 	if (H == 1'b1) begin
			y <= LR;
		end else if (L == 1'b1 && R == 1'b1) begin
			y <= IDLE;
		end else if (R == 1'b1) begin
			y <= RA;
		end else if (L == 1'b1) begin
			y <= LA;
		end else begin
			y <= IDLE;
		end
LA : 	if (H == 1'b1) begin
			y <= LR;
		end else if (L == 1'b1 && R == 1'b1) begin
			y <= IDLE;
		end else if (R == 1'b1) begin
			y <= IDLE;
		end else if (L == 1'b1) begin
			y <= LB;
		end else begin
			y <= IDLE;
		end
LB : 	if (H == 1'b1) begin
			y <= LR;
		end else if (L == 1'b1 && R == 1'b1) begin
			y <= IDLE;
		end else if (R == 1'b1) begin
			y <= IDLE;
		end else if (L == 1'b1) begin
			y <= LC;
		end else begin
			y <= IDLE;
		end
LC : 	if (H == 1'b1) begin
			y <= LR;
		end else if (L == 1'b1 && R == 1'b1) begin
			y <= IDLE;
		end else if (R == 1'b1) begin
			y <= IDLE;
		end else if (L == 1'b1) begin
			y <= IDLE;
		end else begin
			y <= IDLE;
		end
RA : 	if (H == 1'b1) begin
			y <= LR;
		end else if (L == 1'b1 && R == 1'b1) begin
			y <= IDLE;
		end else if (R == 1'b1) begin
			y <= RB;
		end else if (L == 1'b1) begin
			y <= IDLE;
		end else begin
			y <= IDLE;
		end
RB : 	if (H == 1'b1) begin
			y <= LR;
		end else if (L == 1'b1 && R == 1'b1) begin
			y <= IDLE;
		end else if (R == 1'b1) begin
			y <= RC;
		end else if (L == 1'b1) begin
			y <= IDLE;
		end else begin
			y <= IDLE;
		end
RC : 	if (H == 1'b1) begin
			y <= LR;
		end else if (L == 1'b1 && R == 1'b1) begin
			y <= IDLE;
		end else if (R == 1'b1) begin
			y <= IDLE;
		end else if (L == 1'b1) begin
			y <= IDLE;
		end else begin
			y <= IDLE;
		end
LR : 	if (H == 1'b1) begin
			y <= IDLE;
		end else if (L == 1'b1 && R == 1'b1) begin
			y <= IDLE;
		end else if (R == 1'b1) begin
			y <= IDLE;
		end else if (L == 1'b1) begin
			y <= IDLE;
		end else begin
			y <= IDLE;
		end
	default: y <= IDLE;
	endcase
end

always@*
begin
	case(y)
		IDLE:begin
			Lights <= 6'b000000;
		end
		RA:begin
			Lights <= 6'b000010;
		end
		RB:begin
			Lights <= 6'b000101;
		end
		RC:begin
			Lights <= 6'b000111;
		end
		LA:begin
			Lights <= 6'b010000;
		end
		LB:begin
			Lights <= 6'b101000;
		end
		LC:begin
			Lights <= 6'b111000;
		end
		LR:begin
			Lights <= 6'b111111;
		end
	endcase
end

endmodule 