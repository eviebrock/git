LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_unsigned.all;

ENTITY FSMalu IS
	PORT(clkin		:	IN STD_LOGIC;
		 operation	:	IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		 A,B		:	IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		 dataready	:	IN STD_LOGIC;
		 results	:	OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
		 carry, overflow	:	OUT STD_LOGIC);
END FSMalu;

ARCHITECTURE Behavior OF FSMalu IS
	COMPONENT addsub
		PORT (AS : IN STD_LOGIC;
		  x2,x1,x0	 : IN STD_LOGIC;
		  y2,y1,y0	 : IN STD_LOGIC;
		  s2,s1,s0	 : OUT STD_LOGIC;
		  cout, overflow		  : OUT STD_LOGIC);
	END COMPONENT;
	
	COMPONENT logic
		PORT (Operation		  : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		  Alogic,Blogic	  : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		  trueFalse		  : OUT STD_LOGIC_VECTOR(2 DOWNTO 0));
	END COMPONENT;
	
	TYPE stateType IS(idle,add, sub, equal, greater, less, equalzero);
	
	SIGNAL state : stateType;
	
	SIGNAL sendone, sendtwo, SENDsig, ADDsubDecider : STD_LOGIC;
	SIGNAL inputA, inputB	: STD_LOGIC_VECTOR(3 DOWNTO 0);

BEGIN

	PROCESS(clkin)
	BEGIN
		IF(rising_edge(clkin)) THEN
			sendone <= dataready;
			sendtwo <= sendone;
			SENDsig <= sendone AND (NOT sendtwo); --rising edge...for falling edge you invert this
			
			
		END IF;
	END PROCESS;
	
	PROCESS(clkin, operation, dataready) 		--these signals are used in this process
	BEGIN
	
	IF(clkin'EVENT AND clkin = '1') THEN 
			CASE state IS
				WHEN idle =>
					IF (SENDsig = '1' AND operation = "000") THEN
						state <= add;
					ELSIF (SENDsig = '1' AND operation = "001") THEN
						state <= sub;
					ELSE
						state <= idle;
					END IF;
					
				WHEN OTHERS =>
					state <= idle;
			END CASE;
	END IF;	
	END PROCESS;
		
--	add1 : addsub PORT MAP ('1', A(2),A(1),A(0), B(2),B(1),B(0),results(2), results(1), results(0), carry, overflow);
--	sub1 : addsub PORT MAP ('0', A(2),A(1),A(0), B(2),B(1),B(0),results(2), results(1), results(0), carry, overflow);

	logic1 : logic PORT MAP (operation, A, B, results);

------	not sure how to change the input of add/sub being used in addsub portmap
	
END Behavior;

--		IF(dataready = '1') THEN
--	
--		CASE operation IS
--			WHEN "000" => 		--ADD
--				results <= A + B;
--			WHEN "001" =>		--SUBTRACT
--				results <= A - B;
--			WHEN "100" =>		--COMPARE IF EQUAL
--				IF(A = B) THEN
--					results <= "0001";
--				ELSE
--					results <= "0000";
--				END IF;
--			WHEN "101" =>		--COMPARE A>B
--				IF(A > B) THEN
--					results <= "0001";
--				ELSE
--					results <= "0000";
--				END IF;
--			WHEN "110" =>		--COMPARE A<B
--				IF(A < B) THEN
--					results <= "0001";
--				ELSE
--					results <= "0000";
--				END IF;
--			WHEN "111" =>		--COMPARE A=0
--				IF(A = "000") THEN
--					results <= "0001";
--				ELSE
--					results <= "0000";
--				END IF;
--			WHEN OTHERS =>
--				results <= "0000";
--		END CASE;
--		
--		END IF;