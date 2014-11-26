-- BCD to 7-segment decoder, outputs 0 to 15

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY lab_6a IS
	PORT ( bcd  : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
		   leds1 : OUT STD_LOGIC_VECTOR(1 TO 7);
		   leds2 : OUT STD_LOGIC_VECTOR(1 TO 7));
END lab_6a;

ARCHITECTURE Behavior OF lab_6a IS
BEGIN
	PROCESS(bcd)
	BEGIN -- add additional bit to bcd, for sign bit (+) or (-), two cases for each number, 1 and -1
		CASE bcd IS				 -- abcdefg
			WHEN "0000"	=> leds1 <= "1111110"; -- 0
						   leds2 <= "0000000";	
			WHEN "0001"	=> leds1 <= "0110000"; -- 1
						   leds2 <= "0000000";	
			WHEN "0010"	=> leds1 <= "1101101"; -- 2
						   leds2 <= "0000000";	
			WHEN "0011"	=> leds1 <= "1111001"; -- 3
						   leds2 <= "0000000";	
			WHEN "0100"	=> leds1 <= "0110011"; -- 4
						   leds2 <= "0000000";	
			WHEN "0101"	=> leds1 <= "1011011"; -- 5
						   leds2 <= "0000000";	
			WHEN "0110"	=> leds1 <= "1011111"; -- 6
						   leds2 <= "0000000";	
			WHEN "0111"	=> leds1 <= "1110000"; -- 7
						   leds2 <= "0000000";	
			WHEN "1000"	=> leds1 <= "1111111"; -- 8
						   leds2 <= "0000000";	
			WHEN "1001"	=> leds1 <= "1110011"; -- 9
						   leds2 <= "0000000";	
			WHEN "1010"	=> leds1 <= "1111110"; -- 10
						   leds2 <= "0110000"; 
			WHEN "1011"	=> leds1 <= "0110000"; -- 11
						   leds2 <= "0110000";
			WHEN "1100"	=> leds1 <= "1101101"; -- 12
						   leds2 <= "0110000";
			WHEN "1101"	=> leds1 <= "1111001"; -- 13
						   leds2 <= "0110000";
			WHEN "1110"	=> leds1 <= "0110011"; -- 14
						   leds2 <= "0110000";
			WHEN "1111" => leds1 <= "1011011"; -- 15
						   leds2 <= "0110000";
			WHEN OTHERS => leds1 <= "-------"; -- idle
						   leds2 <= "-------";					
		END CASE;
	END PROCESS;
	
	
END Behavior;
			
			
			
			
--LIBRARY ieee;
--USE ieee.std_logic_1164.all;
--
--ENTITY lab10 IS
--	PORT (Clk2, Lft2, Rt2, Haz2: IN STD_LOGIC;
--			Lights2			   : OUT STD_LOGIC_VECTOR(5 DOWNTO 0));
--END lab10;
--
--ARCHITECTURE Behavior OF lab10 IS
--	SIGNAL lightclock: STD_LOGIC;
--	
--	COMPONENT clockdiv
--		PORT (iclk: IN STD_LOGIC;
--			  oclk: OUT STD_LOGIC);
--	END COMPONENT;
--	
--	COMPONENT statemachine
--		PORT (Clk, Lft, Rt, Haz : IN STD_LOGIC;
--			  Lights: OUT STD_LOGIC_VECTOR (5 DOWNTO 0)); --consists of LA-LC AND RA-RC
--	END COMPONENT;
--	
--BEGIN 
--	CLKdiv : clockdiv PORT MAP (Clk2, lightclock);
--	STATEMACH : statemachine PORT MAP(lightclock, Lft2, Rt2, Haz2, Lights2);
--	
--END Behavior;