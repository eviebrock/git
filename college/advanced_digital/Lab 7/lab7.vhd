LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_unsigned.all;
use ieee.numeric_std.all; -- number conversion in memory


ENTITY lab_7 IS
	PORT(clkin, reset, readwrite		:	IN STD_LOGIC;
		 operation					:	IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		 A,B						:	IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		 dataready					:	IN STD_LOGIC;
		 readlocation,writelocation : BUFFER STD_LOGIC_VECTOR(1 DOWNTO 0);
		 seg1,seg2,seg3,seg4 		: OUT STD_LOGIC_VECTOR(1 TO 7);
		 pn1,pn2,pn3				:	OUT STD_LOGIC; --pos/neg value high/low
		 carry, overflow			:	OUT STD_LOGIC; --needed for arithmetic part
		 realanswer					:	BUFFER STD_LOGIC_VECTOR(2 DOWNTO 0); -- stores answer
		 dataout					: BUFFER STD_LOGIC_VECTOR(8 DOWNTO 0)); --holds value from memory output
END lab_7;

ARCHITECTURE Behavior OF lab_7 IS	

	SIGNAL datain : STD_LOGIC_VECTOR(8 downto 0);
	SIGNAL x1, y1, op1, aluanswer : STD_LOGIC_VECTOR(2 DOWNTO 0);
	SIGNAL memaddr : STD_LOGIC_VECTOR(1 DOWNTO 0);
	SIGNAL datareadysyncsig, drrisesig, drfallsig  : STD_LOGIC;
	
	COMPONENT memory
		PORT(clk, reset, en		: IN STD_LOGIC;
		     addr				: IN STD_LOGIC_VECTOR(1 DOWNTO 0);
		     datain				: IN STD_LOGIC_VECTOR(8 DOWNTO 0);
		     dataout			: OUT STD_LOGIC_VECTOR(8 DOWNTO 0));
	END COMPONENT;
	
	COMPONENT FSM
		PORT(clkin					:	IN STD_LOGIC;
		 operation					:	IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		 A,B						:	IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		 fallsig					:	IN STD_LOGIC;
		 realanswer					:	OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
		 carry, overflow		 	:	BUFFER STD_LOGIC); --needed for arithmetic part
	END COMPONENT;

	COMPONENT sevensegment
		PORT ( Adisplay, Bdisplay, OPdisplay,ResultDisplay   : IN STD_LOGIC_VECTOR(2 DOWNTO 0); -- ResultDisplay
			   leds1, leds2, leds3, leds4    				 : OUT STD_LOGIC_VECTOR(1 TO 7);
			   posneg1, posneg2, posneg3  					 : OUT STD_LOGIC);
	END COMPONENT;
	
	COMPONENT synch
		PORT( 	clock,sig1	: IN STD_LOGIC;
			rise,fall	: OUT STD_LOGIC;
			sigsync		: BUFFER STD_LOGIC);
	END COMPONENT;

BEGIN

	datain <= A&B&operation;
	aluanswer <= realanswer;
				
	x1 <= dataout(8 downto 6);
	y1 <= dataout(5 downto 3);
	op1 <= dataout(2 downto 0);
	
	memaddr <= writelocation WHEN readwrite='0' ELSE readlocation;

	MainMem : memory PORT MAP (clkin, reset, readwrite, memaddr, datain, dataout);
	SEVSEGMENTarith : sevensegment PORT MAP (x1,y1,op1,aluanswer,seg1,seg2,seg3,seg4, pn1, pn2, pn3);
	ALU : FSM PORT MAP (clkin, op1, x1, y1, drfallsig, realanswer, carry, overflow);
	datasynch: synch PORT MAP (clkin,dataready, drrisesig, drfallsig, datareadysyncsig);

	PROCESS(clkin,reset) -- changes in these inputs lead to process activation
	BEGIN
		IF (reset = '0') THEN
			readlocation <= "00";
			writelocation <= "00";

		ELSIF(clkin'EVENT AND clkin = '1') THEN 
			IF(drfallsig = '1') THEN
				IF (readwrite = '0') then --write
					IF (writelocation = "11") then
						writelocation <= "00";
					else
						writelocation <= writelocation +1;
					end if;
				else 
					IF (readlocation = "11") then
						readlocation <= "00";
					else
						readlocation <= readlocation +1;
					end if;
				end if;
			END IF;			
		END IF;
	END PROCESS;		
END Behavior;