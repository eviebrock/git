LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY masterclk IS
    PORT ( iclk 		: IN STD_LOGIC;
	   oclk		: OUT STD_LOGIC);
END masterclk;

ARCHITECTURE Behavior OF masterclk IS
CONSTANT halfcount : POSITIVE := 135000; -- original divider is 13500000, 135000 counts 1/100 second
SIGNAL Count:  INTEGER RANGE 0 TO halfcount-1; 
SIGNAL clkstate :   STD_LOGIC;
BEGIN
    PROCESS ( iclk )
	BEGIN
		IF (iclk'EVENT AND iclk = '1') THEN
			IF Count = halfcount-1 THEN	
				Count <= 0;
				clkstate <= not clkstate;
			ELSE
				Count <= Count + 1;
			END IF;
		END IF;
	END PROCESS;
	oclk <= clkstate;
END Behavior;
