LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY lab_4 IS
	PORT(d, n, reset, clk : IN STD_LOGIC;
					candy : OUT STD_LOGIC);
END lab_4;

ARCHITECTURE BEHAVIOR OF lab_4 IS
	SIGNAL rise_d 	  : STD_LOGIC;
	SIGNAL rise_n 	  : STD_LOGIC;
	SIGNAL rise_reset : STD_LOGIC;
	SIGNAL d1 		  : STD_LOGIC;
	SIGNAL d2		  : STD_LOGIC;
	SIGNAL d3 		  : STD_LOGIC;
	SIGNAL n1 		  : STD_LOGIC;
	SIGNAL n2 		  : STD_LOGIC;
	SIGNAL n3 		  : STD_LOGIC;
	SIGNAL reset1 	  : STD_LOGIC;
	SIGNAL reset2 	  : STD_LOGIC;
	SIGNAL reset3 	  : STD_LOGIC;
	
	TYPE STATE_TYPE IS (s1, s2, s3, s4, s5);
	SIGNAL Y : STATE_TYPE:=s1;
	
	BEGIN

	PROCESS(clk)

	BEGIN
     IF(rising_edge(clk)) THEN
          d1 <= d;
          d2 <= d1;
          d3 <= d2;
          rise_d <= (NOT d3) AND d2;
          
          n1 <= n;
          n2 <= n1;
          n3 <= n2;
          rise_n <= (NOT n3) AND n2;
          
          reset1 <= reset;
          reset2 <= reset1;
          reset3 <= reset2;
          rise_reset <= (NOT reset3) AND reset2;

	CASE y IS
		WHEN S1=>
		IF rise_d = '1' AND rise_n = '0' AND rise_reset = '0' THEN y <= s3;
		ELSIF rise_n = '1' AND rise_d = '0' AND rise_reset = '0' THEN y <= s2;
		ELSIF rise_d = '0' AND rise_n = '0' AND rise_reset = '0' THEN y <= s1;
		ELSE y <= s1;
		END IF;
		
		WHEN S2=>
		IF rise_d = '1' AND rise_n = '0' AND rise_reset = '0' THEN y <= s4;
		ELSIF rise_n = '1' AND rise_d = '0' AND rise_reset = '0' THEN y <= s3;
		ELSIF rise_d = '0' AND rise_n = '0' AND rise_reset = '0' THEN y <= s2;
		ELSE y <= s1;
		END IF;
		
		WHEN S3=>
		IF rise_d = '1' AND rise_n = '0' AND rise_reset = '0' THEN y <= s5;
		ELSIF rise_n = '1' AND rise_d = '0' AND rise_reset = '0' THEN y <= s4;
		ELSIF rise_d = '0' AND rise_n = '0' AND rise_reset = '0' THEN y <= s3;
		ELSE y <= s1;
		END IF;
		
		WHEN S4=>
		IF rise_d = '1' AND rise_n = '0' AND rise_reset = '0' THEN y <= s5;
		ELSIF rise_n = '1' AND rise_d = '0' AND rise_reset = '0' THEN y <= s5;
		ELSIF rise_d = '0' AND rise_n = '0' AND rise_reset = '0' THEN y <= s4;
		ELSE y <= s1;
		END IF;
		
		WHEN S5=>
		IF rise_d = '1' AND rise_n = '0' AND rise_reset = '0' THEN y <= s5;
		ELSIF rise_n = '1' AND rise_d = '0' AND rise_reset = '0' THEN y <= s5;
		ELSIF rise_d = '0' AND rise_n = '0' AND rise_reset = '0' THEN y <= s5;
		ELSE y <= s1;
		END IF;

		END CASE;
		
	END IF;
	
END PROCESS;

candy <= '1' WHEN y = s5 ELSE '0';

END BEHAVIOR;