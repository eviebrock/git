LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_unsigned.all;
use ieee.numeric_std.all; -- number conversion in memory

ENTITY FSM IS
	PORT(clkin						:	IN STD_LOGIC;
		 operation					:	IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		 A,B						:	IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		 fallsig					:	IN STD_LOGIC;
		 realanswer					:	OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
		 carry, overflow			:	BUFFER STD_LOGIC); --needed for arithmetic part
		
END FSM;

ARCHITECTURE Behavior OF FSM IS
	
	COMPONENT addsub 
		PORT (
		  AS : IN STD_LOGIC;
		  x	 : IN STD_LOGIC_VECTOR (2 downto 0);
		  y	 : IN STD_LOGIC_VECTOR (2 downto 0);
		  s	 : OUT STD_LOGIC_VECTOR (2 downto 0);
		  cout, overflow		  : OUT STD_LOGIC);
	END COMPONENT;
	
	COMPONENT logic
		PORT (doOperation	  : IN STD_LOGIC;
		  Operation		  : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		  Alogic,Blogic	  : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		  trueFalse		  : OUT STD_LOGIC_VECTOR(2 DOWNTO 0));
	END COMPONENT;
	
	TYPE stateType IS(idle,save, load, add, sub, equal, greater, less, equalzero);
	
	SIGNAL state : stateType;
	
	SIGNAL sevseg1,sevseg2,sevseg3,sevseg4 : STD_LOGIC_VECTOR (1 TO 7);
	
	SIGNAL additionsubtraction  : STD_LOGIC;
	SIGNAL results,results2,REALresult : STD_LOGIC_VECTOR (2 downto 0);
	SIGNAL x1, y1, op1 : STD_LOGIC_VECTOR(2 DOWNTO 0);
	
BEGIN

			
	
	
	PROCESS(clkin) 		--these signals are used in this process
	BEGIN

	IF(clkin'EVENT AND clkin = '1') THEN 
			CASE state IS
							
				WHEN idle =>				
					
					IF (operation = "000" AND fallsig = '1' ) THEN
						state <= add;
						additionsubtraction <= '0';
					ELSIF (operation = "001" AND fallsig = '1' ) THEN
						state <= sub;
						additionsubtraction <= '1';
					ELSIF (operation = "100" AND fallsig = '1' ) THEN
						state <= equal;
					ELSIF (operation = "101" AND fallsig = '1' ) THEN
						state <= greater;
					ELSIF (operation = "110" AND fallsig = '1' ) THEN
						state <= less;
					ELSIF (operation = "111" AND fallsig = '1' ) THEN
						state <= equalzero;
					ELSE
						state <= idle;
					END IF;
					
				WHEN add =>
					
					REALresult <= results;
					
					IF (operation = "000" AND fallsig = '1' ) THEN
						state <= add;
						additionsubtraction <= '0';
					ELSIF (operation = "001" AND fallsig = '1' ) THEN
						state <= sub;
						additionsubtraction <= '1';
					ELSIF (operation = "100" AND fallsig = '1' ) THEN
						state <= equal;
					ELSIF (operation = "101" AND fallsig = '1' ) THEN
						state <= greater;
					ELSIF (operation = "110" AND fallsig = '1' ) THEN
						state <= less;
					ELSIF (operation = "111" AND fallsig = '1' ) THEN
						state <= equalzero;
					ELSE
						state <= idle;
					END IF;
					
				WHEN sub =>
				
					REALresult <= results;
				
					IF (operation = "000" AND fallsig = '1' ) THEN
						state <= add;
						additionsubtraction <= '0';
					ELSIF (operation = "001" AND fallsig = '1' ) THEN
						state <= sub;
						additionsubtraction <= '1';
					ELSIF (operation = "100" AND fallsig = '1' ) THEN
						state <= equal;
					ELSIF (operation = "101" AND fallsig = '1' ) THEN
						state <= greater;
					ELSIF (operation = "110" AND fallsig = '1' ) THEN
						state <= less;
					ELSIF (operation = "111" AND fallsig = '1' ) THEN
						state <= equalzero;
					ELSE
						state <= idle;
					END IF;
					
				WHEN equal =>
				
					REALresult <= results2;
				
					IF (operation = "000" AND fallsig = '1' ) THEN
						state <= add;
						additionsubtraction <= '0';
					ELSIF (operation = "001" AND fallsig = '1' ) THEN
						state <= sub;
						additionsubtraction <= '1';
					ELSIF (operation = "100" AND fallsig = '1' ) THEN
						state <= equal;
					ELSIF (operation = "101" AND fallsig = '1' ) THEN
						state <= greater;
					ELSIF (operation = "110" AND fallsig = '1' ) THEN
						state <= less;
					ELSIF (operation = "111" AND fallsig = '1' ) THEN
						state <= equalzero;
					ELSE
						state <= idle;
					END IF;
					
				WHEN greater =>
				
					REALresult <= results2;
				
					IF (operation = "000" AND fallsig = '1' ) THEN
						state <= add;
						additionsubtraction <= '0';
					ELSIF (operation = "001" AND fallsig = '1' ) THEN
						state <= sub;
						additionsubtraction <= '1';
					ELSIF (operation = "100" AND fallsig = '1' ) THEN
						state <= equal;
					ELSIF (operation = "101" AND fallsig = '1' ) THEN
						state <= greater;
					ELSIF (operation = "110" AND fallsig = '1' ) THEN
						state <= less;
					ELSIF (operation = "111" AND fallsig = '1' ) THEN
						state <= equalzero;
					ELSE
						state <= idle;
					END IF;
					
				WHEN less =>
				
					REALresult <= results2;
				
					IF (operation = "000" AND fallsig = '1' ) THEN
						state <= add;
						additionsubtraction <= '0';
					ELSIF (operation = "001" AND fallsig = '1' ) THEN
						state <= sub;
						additionsubtraction <= '1';
					ELSIF (operation = "100" AND fallsig = '1' ) THEN
						state <= equal;
					ELSIF (operation = "101" AND fallsig = '1' ) THEN
						state <= greater;
					ELSIF (operation = "110" AND fallsig = '1' ) THEN
						state <= less;
					ELSIF (operation = "111" AND fallsig = '1' ) THEN
						state <= equalzero;
					ELSE
						state <= idle;
					END IF;
					
				WHEN equalzero =>
				
					REALresult <= results2;
				
					IF (operation = "000" AND fallsig = '1' ) THEN
						state <= add;
						additionsubtraction <= '0';
					ELSIF (operation = "001" AND fallsig = '1' ) THEN
						state <= sub;
						additionsubtraction <= '1';
					ELSIF (operation = "100" AND fallsig = '1' ) THEN
						state <= equal;
					ELSIF (operation = "101" AND fallsig = '1' ) THEN
						state <= greater;
					ELSIF (operation = "110" AND fallsig = '1' ) THEN
						state <= less;
					ELSIF (operation = "111" AND fallsig = '1' ) THEN
						state <= equalzero;
					ELSE
						state <= idle;
					END IF;
					
				WHEN OTHERS => 
					state <= idle;
			END CASE;
		END IF;	
	END PROCESS;
	
	AddSubA : addsub PORT MAP (additionsubtraction, A,B, results, carry, overflow); --additionsubtraction =1 subtracting , =0 adding
	logicA : logic PORT MAP (fallsig,operation, A,B, results2);
	realanswer <= REALresult;
	
END Behavior;