LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY seven_seg_hex IS
	PORT(x	:IN		STD_LOGIC_VECTOR(3 DOWNTO 0);
		 h	:OUT	STD_LOGIC_VECTOR(6 DOWNTO 0));
	END seven_seg_hex;
	
ARCHITECTURE Behavior OF seven_seg_hex IS
	SIGNAL Nh : STD_LOGIC_VECTOR(6 DOWNTO 0);
	BEGIN
		WITH x SELECT
			Nh <= "0111111" WHEN "0000",
				 "0000110" WHEN "0001",
				 "1011011" WHEN "0010",
				 "1001111" WHEN "0011",
				 "1100110" WHEN "0100",
				 "1101101" WHEN "0101",
				 "1111101" WHEN "0110",
				 "0000111" WHEN "0111",
				 "1111111" WHEN "1000",
				 "1100111" WHEN "1001",
				 "1110111" WHEN "1010",
				 "1111100" WHEN "1011",
				 "0111001" WHEN "1100",
				 "1011110" WHEN "1101",
				 "1111001" WHEN "1110",
				 "1110001" WHEN OTHERS;
			h <= NOT Nh;
	END Behavior;
