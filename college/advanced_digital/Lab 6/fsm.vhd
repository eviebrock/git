-- FSM

LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_unsigned.all;

ENTITY FSMalu IS
	PORT(clkin		:	IN STD_LOGIC;
		 operation	:	IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		 A,B		:	IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		 dataready	:	IN STD_LOGIC;
		 seg1,seg2,seg3,seg4 : OUT STD_LOGIC_VECTOR(1 TO 7);
		 pn1,pn2,pn3	:	OUT STD_LOGIC;
		 carry, overflow	:	OUT STD_LOGIC);
END FSMalu;

ARCHITECTURE Behavior OF FSMalu IS
	
	COMPONENT addsub
		PORT (doAS : IN STD_LOGIC;
		  AS : IN STD_LOGIC;
		  OP,x	 : IN STD_LOGIC_VECTOR (2 downto 0);
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
	
	COMPONENT sevensegment
		PORT (	Adisplay,Bdisplay,OPdisplay, ResultDisplay  : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		leds1 : OUT STD_LOGIC_VECTOR(1 TO 7);
		leds2 : OUT STD_LOGIC_VECTOR(1 TO 7);
		leds3 : OUT STD_LOGIC_VECTOR(1 TO 7);
		leds4 : OUT STD_LOGIC_VECTOR(1 TO 7);
		posneg1, posneg2, posneg3  : OUT STD_LOGIC);
	END COMPONENT;
	
	TYPE stateType IS(idle,add, sub, equal, greater, less, equalzero);
	
	SIGNAL state : stateType;
	
	SIGNAL sevseg1,sevseg2,sevseg3,sevseg4 : STD_LOGIC_VECTOR (1 TO 7);
	
	SIGNAL sendone, sendtwo, SENDsig,Decider  : STD_LOGIC;
	SIGNAL results,results2,REALresult : STD_LOGIC_VECTOR (2 downto 0);
	
	SIGNAL count: INTEGER RANGE 0 TO 13500000; --used in clock division
	
	SIGNAL clkstate, clock: std_logic; --used in clock division

BEGIN

	PROCESS(clkin)
	BEGIN
		IF(clkin'EVENT AND clkin ='1') THEN
			IF count = 13500000 THEN
				count <= 0;
				clkstate <= not clkstate;

			ELSE
				count <= count +1;
				clkstate <= clkstate;
				
			END IF;
			clock <= clkstate;
		END IF;
	END PROCESS;

	PROCESS(clock)
	BEGIN
		IF(rising_edge(clock)) THEN
			sendone <= not dataready;
			sendtwo <= sendone;
			SENDsig <= sendone AND (NOT sendtwo); --rising edge...for falling edge you invert this

		END IF;
	END PROCESS;
	
	PROCESS(clock, operation, dataready, Decider) 		--these signals are used in this process
	BEGIN
	
	IF(clock'EVENT AND clock = '1') THEN 
			CASE state IS
				WHEN idle =>
				
				
				
					IF (operation = "000" AND SENDsig = '0') THEN
						state <= add;
			
					ELSIF (operation = "001" AND SENDsig = '0') THEN
						state <= sub;
			
					ELSIF (operation = "100" AND SENDsig = '0') THEN
						state <= equal;
					ELSIF (operation = "101" AND SENDsig = '0') THEN
						state <= greater;
					ELSIF (operation = "110" AND SENDsig = '0') THEN
						state <= less;
					ELSIF (operation = "111" AND SENDsig = '0') THEN
						state <= equalzero;
					ELSIF (operation = "000" AND SENDsig = '1') THEN
						state <= add;
						Decider <= '0';
					ELSIF (operation = "001" AND SENDsig = '1') THEN
						state <= sub;
						Decider <= '1';
					ELSIF (operation = "100" AND SENDsig = '1') THEN
						state <= equal;
					ELSIF (operation = "101" AND SENDsig = '1') THEN
						state <= greater;
					ELSIF (operation = "110" AND SENDsig = '1') THEN
						state <= less;
					ELSIF (operation = "111" AND SENDsig = '1') THEN
						state <= equalzero;
					ELSE
						state <= idle;
					END IF;
				WHEN add =>
					
					REALresult <= results;
					
					IF (operation = "000" AND SENDsig = '0') THEN
						state <= add;
			
					ELSIF (operation = "001" AND SENDsig = '0') THEN
						state <= sub;
			
					ELSIF (operation = "100" AND SENDsig = '0') THEN
						state <= equal;
					ELSIF (operation = "101" AND SENDsig = '0') THEN
						state <= greater;
					ELSIF (operation = "110" AND SENDsig = '0') THEN
						state <= less;
					ELSIF (operation = "111" AND SENDsig = '0') THEN
						state <= equalzero;
					ELSIF (operation = "000" AND SENDsig = '1') THEN
						state <= add;
						Decider <= '0';
					ELSIF (operation = "001" AND SENDsig = '1') THEN
						state <= sub;
						Decider <= '1';
					ELSIF (operation = "100" AND SENDsig = '1') THEN
						state <= equal;
					ELSIF (operation = "101" AND SENDsig = '1') THEN
						state <= greater;
					ELSIF (operation = "110" AND SENDsig = '1') THEN
						state <= less;
					ELSIF (operation = "111" AND SENDsig = '1') THEN
						state <= equalzero;
					ELSE
						state <= idle;
					END IF;
				WHEN sub =>
				
					REALresult <= results;
				
					IF (operation = "000" AND SENDsig = '0') THEN
						state <= add;
			
					ELSIF (operation = "001" AND SENDsig = '0') THEN
						state <= sub;
			
					ELSIF (operation = "100" AND SENDsig = '0') THEN
						state <= equal;
					ELSIF (operation = "101" AND SENDsig = '0') THEN
						state <= greater;
					ELSIF (operation = "110" AND SENDsig = '0') THEN
						state <= less;
					ELSIF (operation = "111" AND SENDsig = '0') THEN
						state <= equalzero;
					ELSIF (operation = "000" AND SENDsig = '1') THEN
						state <= add;
						Decider <= '0';
					ELSIF (operation = "001" AND SENDsig = '1') THEN
						state <= sub;
						Decider <= '1';
					ELSIF (operation = "100" AND SENDsig = '1') THEN
						state <= equal;
					ELSIF (operation = "101" AND SENDsig = '1') THEN
						state <= greater;
					ELSIF (operation = "110" AND SENDsig = '1') THEN
						state <= less;
					ELSIF (operation = "111" AND SENDsig = '1') THEN
						state <= equalzero;
					ELSE
						state <= idle;
					END IF;
				WHEN equal =>
				
				REALresult <= results2;
					IF (operation = "000" AND SENDsig = '0') THEN
						state <= add;
			
					ELSIF (operation = "001" AND SENDsig = '0') THEN
						state <= sub;
			
					ELSIF (operation = "100" AND SENDsig = '0') THEN
						state <= equal;
					ELSIF (operation = "101" AND SENDsig = '0') THEN
						state <= greater;
					ELSIF (operation = "110" AND SENDsig = '0') THEN
						state <= less;
					ELSIF (operation = "111" AND SENDsig = '0') THEN
						state <= equalzero;
					ELSIF (operation = "000" AND SENDsig = '1') THEN
						state <= add;
						Decider <= '0';
					ELSIF (operation = "001" AND SENDsig = '1') THEN
						state <= sub;
						Decider <= '1';
					ELSIF (operation = "100" AND SENDsig = '1') THEN
						state <= equal;
					ELSIF (operation = "101" AND SENDsig = '1') THEN
						state <= greater;
					ELSIF (operation = "110" AND SENDsig = '1') THEN
						state <= less;
					ELSIF (operation = "111" AND SENDsig = '1') THEN
						state <= equalzero;
					ELSE
						state <= idle;
					END IF;
				WHEN greater =>
				
				REALresult <= results2;
				
					IF (operation = "000" AND SENDsig = '0') THEN
						state <= add;
			
					ELSIF (operation = "001" AND SENDsig = '0') THEN
						state <= sub;
			
					ELSIF (operation = "100" AND SENDsig = '0') THEN
						state <= equal;
					ELSIF (operation = "101" AND SENDsig = '0') THEN
						state <= greater;
					ELSIF (operation = "110" AND SENDsig = '0') THEN
						state <= less;
					ELSIF (operation = "111" AND SENDsig = '0') THEN
						state <= equalzero;
					ELSIF (operation = "000" AND SENDsig = '1') THEN
						state <= add;
						Decider <= '0';
					ELSIF (operation = "001" AND SENDsig = '1') THEN
						state <= sub;
						Decider <= '1';
					ELSIF (operation = "100" AND SENDsig = '1') THEN
						state <= equal;
					ELSIF (operation = "101" AND SENDsig = '1') THEN
						state <= greater;
					ELSIF (operation = "110" AND SENDsig = '1') THEN
						state <= less;
					ELSIF (operation = "111" AND SENDsig = '1') THEN
						state <= equalzero;
					ELSE
						state <= idle;
					END IF;
				WHEN less =>
				
				REALresult <= results2;
				
					IF (operation = "000" AND SENDsig = '0') THEN
						state <= add;
			
					ELSIF (operation = "001" AND SENDsig = '0') THEN
						state <= sub;
			
					ELSIF (operation = "100" AND SENDsig = '0') THEN
						state <= equal;
					ELSIF (operation = "101" AND SENDsig = '0') THEN
						state <= greater;
					ELSIF (operation = "110" AND SENDsig = '0') THEN
						state <= less;
					ELSIF (operation = "111" AND SENDsig = '0') THEN
						state <= equalzero;
					ELSIF (operation = "000" AND SENDsig = '1') THEN
						state <= add;
						Decider <= '0';
					ELSIF (operation = "001" AND SENDsig = '1') THEN
						state <= sub;
						Decider <= '1';
					ELSIF (operation = "100" AND SENDsig = '1') THEN
						state <= equal;
					ELSIF (operation = "101" AND SENDsig = '1') THEN
						state <= greater;
					ELSIF (operation = "110" AND SENDsig = '1') THEN
						state <= less;
					ELSIF (operation = "111" AND SENDsig = '1') THEN
						state <= equalzero;
					ELSE
						state <= idle;
					END IF;
				WHEN equalzero =>
				
				REALresult <= results2;
				
					IF (operation = "000" AND SENDsig = '0') THEN
						state <= add;
			
					ELSIF (operation = "001" AND SENDsig = '0') THEN
						state <= sub;
			
					ELSIF (operation = "100" AND SENDsig = '0') THEN
						state <= equal;
					ELSIF (operation = "101" AND SENDsig = '0') THEN
						state <= greater;
					ELSIF (operation = "110" AND SENDsig = '0') THEN
						state <= less;
					ELSIF (operation = "111" AND SENDsig = '0') THEN
						state <= equalzero;
					ELSIF (operation = "000" AND SENDsig = '1') THEN
						state <= add;
						Decider <= '0';
					ELSIF (operation = "001" AND SENDsig = '1') THEN
						state <= sub;
						Decider <= '1';
					ELSIF (operation = "100" AND SENDsig = '1') THEN
						state <= equal;
					ELSIF (operation = "101" AND SENDsig = '1') THEN
						state <= greater;
					ELSIF (operation = "110" AND SENDsig = '1') THEN
						state <= less;
					ELSIF (operation = "111" AND SENDsig = '1') THEN
						state <= equalzero;
					ELSE
						state <= idle;
					END IF;
				WHEN OTHERS => 
					state <= idle;
			END CASE;
	END IF;	
	END PROCESS;
	
	AddSubA : addsub PORT MAP (SENDsig,Decider,operation, A,B, results, carry, overflow); --decider =1 subtracting , =0 adding
	logicA : logic PORT MAP (SENDsig,operation, A, B, results2);
	
	SEVSEGMENTarith : sevensegment PORT MAP (A,B,operation,REALresult,seg1,seg2,seg3,seg4, pn1, pn2, pn3);
	--SEVSEGMENTlogic : sevensegment PORT MAP (A,B,operation,results2,seg1,seg2,seg3,seg4);
	
END Behavior;