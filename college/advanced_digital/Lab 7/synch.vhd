LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY synch IS
	PORT( 	clock,sig1	: IN STD_LOGIC;
			rise,fall	: OUT STD_LOGIC;
			sigsync		: BUFFER STD_LOGIC);
END synch;
	
ARCHITECTURE Behavior OF synch IS	
		
		SIGNAL resync1 : STD_LOGIC;

BEGIN
	PROCESS(clock)
	BEGIN
		IF(rising_edge(clock)) THEN
			resync1 <= sig1;
			sigsync <= resync1;
			rise <= resync1 AND (NOT sigsync); --rising edge...for falling edge you invert this
			fall <= (not resync1) and sigsync;
			
		END IF;
	END PROCESS;
	
END Behavior;