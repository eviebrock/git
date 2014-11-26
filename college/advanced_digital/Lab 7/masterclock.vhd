LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY masterclock IS
	PORT (clkin : IN STD_LOGIC;
		  outclock : OUT STD_LOGIC);
END masterclock;
		
ARCHITECTURE Behavior OF masterclock IS
		
	SIGNAL count: INTEGER RANGE 0 TO 13500000; --used in clock division
	SIGNAL clkstate, clock: std_logic; --used in clock division
BEGIN
	
	PROCESS(clkin)
	BEGIN
		IF(clkin'EVENT AND clkin ='1') THEN
			IF count = 1 THEN
				count <= 0;
				clkstate <= not clkstate;

			ELSE
				count <= count +1;
				clkstate <= clkstate;
				
			END IF;
			clock <= clkstate;
		END IF;
	END PROCESS;
	
END Behavior;