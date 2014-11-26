-- logic

LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_signed.all;
ENTITY logic IS
	PORT (doOperation	  : IN STD_LOGIC;
		  Operation		  : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		  Alogic,Blogic	  : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		  trueFalse		  : OUT STD_LOGIC_VECTOR(2 DOWNTO 0));
END logic;

ARCHITECTURE Structure OF logic IS

	SIGNAL tempBOOL : STD_LOGIC_VECTOR (2 DOWNTO 0);

	BEGIN 		
		PROCESS(doOperation, Operation,Alogic,Blogic)
		BEGIN 
		
		if(doOperation = '1') then

		CASE Operation IS
			WHEN "100" =>		--COMPARE IF EQUAL
				IF(Alogic = Blogic) THEN
					tempBOOL <= "001";
				ELSE
					tempBOOL <= "000";
				END IF;
			WHEN "101" =>		--COMPARE A>B
				IF(Alogic > Blogic) THEN
					tempBOOL <= "001";
				ELSE
					tempBOOL <= "000";
				END IF;
			WHEN "110" =>		--COMPARE A<B
				IF(Alogic < Blogic) THEN
					tempBOOL <= "001";
				ELSE
					tempBOOL <= "000";
				END IF;
			WHEN "111" =>		--COMPARE A=0
				IF(Alogic = "000") THEN
					tempBOOL <= "001";
				ELSE
					tempBOOL <= "000";
				END IF;
			WHEN OTHERS =>
				tempBOOL <= "000";
		END CASE;
		
		end if;
			
		END PROCESS;	
		
		trueFalse <= "001" WHEN (tempBOOL = "001" AND doOperation = '1') else "000";
	
END Structure;
		
		
--		WHEN bcd <= "0000" WHEN => leds1 <= "1111110"; -- 0
--      leds2 <= "0000000"; 
--		WHEN bcd <= "0001" => leds1 <= "0110000"; -- 1
--		leds2 <= "0000000"; 
--		WHEN bcd <= "0010" => leds1 <= "1101101"; -- 2
--		leds2 <= "0000000"; 
--		WHEN bcd <= "0011" => leds1 <= "1111001"; -- 3
--		leds2 <= "0000000"; 
--		WHEN bcd <= "0100" => leds1 <= "0110011"; -- 4
--		leds2 <= "0000000"; 
--		WHEN bcd <= "0101" => leds1 <= "1011011"; -- 5
--		leds2 <= "0000000"; 
--		WHEN bcd <= "0110" => leds1 <= "1011111"; -- 6
--		leds2 <= "0000000"; 
--		WHEN bcd <= "0111" => leds1 <= "1110000"; -- 7
--		leds2 <= "0000000"; 
--		WHEN bcd <= "1000" => leds1 <= "1111111"; -- 8
--		leds2 <= "0000000"; 
--		WHEN bcd <= "1001" => leds1 <= "1110011"; -- 9
--		leds2 <= "0000000"; 
--		WHEN bcd <= "1010" => leds1 <= "1111110"; -- 10
--		leds2 <= "0110000"; 
--		WHEN bcd <= "1011" => leds1 <= "0110000"; -- 11
--		leds2 <= "0110000";
--		WHEN bcd <= "1100" => leds1 <= "1101101"; -- 12
--		leds2 <= "0110000";
--		WHEN bcd <= "1101" => leds1 <= "1111001"; -- 13
--		leds2 <= "0110000";
--		WHEN bcd <= "1110" => leds1 <= "0110011"; -- 14
--		leds2 <= "0110000";
--		WHEN bcd <= "1111" => leds1 <= "1011011"; -- 15
--		leds2 <= "0110000";
--		WHEN OTHERS => leds1 <= "-------"; -- idle
--		leds2 <= "-------";     	
		
--END Operation;

-- add/sub

--LIBRARY ieee;
--USE ieee.std_logic_1164.all;
--USE ieee.std_logic_signed.all;
--ENTITY lab_6 IS
--	PORT (AS : IN STD_LOGIC;
--		  x	 : IN STD_LOGIC_VECTOR (2 downto 0);
--		  y	 : IN STD_LOGIC_VECTOR (2 downto 0);
--		  s	 : OUT STD_LOGIC_VECTOR (2 downto 0);
--		  cout, overflow		  : OUT STD_LOGIC);
--END lab_6;
--ARCHITECTURE Structure OF lab_6 IS
--	Signal yAS : STD_LOGIC_VECTOR (2 downto 0);
--	COMPONENT adder
--		PORT (	cin		  	: IN STD_LOGIC;
--				x : IN STD_LOGIC_VECTOR (2 downto 0);
--				y : IN STD_LOGIC_VECTOR (2 downto 0);
--				s : OUT STD_LOGIC_VECTOR (2 downto 0);
--				cout, overflow		  : OUT STD_LOGIC);
--	END COMPONENT;
--BEGIN 
--		stage0:	adder PORT MAP(AS,x,yAS,s,cout,overflow);
--			yAS(0) <= y(0) xor AS; --since its 2 downto 0, LSB is 0
--			yAS(1) <= y(1) xor AS;
--			yAS(2) <= y(2) xor AS; --number representation is in signed decimal
--								   --having # rep. in ASCII does not give correct results
--								   --when incorrect output reached there is overflow		
--END Structure;

-- 7 segment

--LIBRARY ieee;
--USE ieee.std_logic_1164.all;
--
--ENTITY lab_6 IS
-- PORT ( bcd  : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
--     leds1 : OUT STD_LOGIC_VECTOR(1 TO 7);
--     leds2 : OUT STD_LOGIC_VECTOR(1 TO 7);
--	 leds3 : OUT STD_LOGIC_VECTOR(1 TO 7);
--	 leds4 : OUT STD_LOGIC_VECTOR(1 TO 7));
--END lab_6;
--
--ARCHITECTURE Behavior OF lab_6 IS
--BEGIN
-- PROCESS(bcd)
-- BEGIN -- add additional bit to bcd, for sign bit (+) or (-), two cases for each number, 1 and -1
--  CASE bcd IS     -- abcdefg
--   WHEN "0000" => leds1 <= "1111110"; -- 0
--         leds2 <= "0000000";
--         leds3 <= "0000000";
--         leds4 <= "0000000"; 
--   WHEN "0001" => leds1 <= "0110000"; -- 1
--         leds2 <= "0000000"; 
--   WHEN "0010" => leds1 <= "1101101"; -- 2
--         leds2 <= "0000000"; 
--   WHEN "0011" => leds1 <= "1111001"; -- 3
--         leds2 <= "0000000"; 
--   WHEN "0100" => leds1 <= "0110011"; -- 4
--         leds2 <= "0000000"; 
--   WHEN "0101" => leds1 <= "1011011"; -- 5
--         leds2 <= "0000000"; 
--   WHEN "0110" => leds1 <= "1011111"; -- 6
--         leds2 <= "0000000"; 
--   WHEN "0111" => leds1 <= "1110000"; -- 7
--         leds2 <= "0000000"; 
--   WHEN "1000" => leds1 <= "1111111"; -- 8
--         leds2 <= "0000000"; 
--   WHEN "1001" => leds1 <= "1110011"; -- 9
--         leds2 <= "0000000"; 
--   WHEN "1010" => leds1 <= "1111110"; -- 10
--         leds2 <= "0110000"; 
--   WHEN "1011" => leds1 <= "0110000"; -- 11
--         leds2 <= "0110000";
--   WHEN "1100" => leds1 <= "1101101"; -- 12
--         leds2 <= "0110000";
--   WHEN "1101" => leds1 <= "1111001"; -- 13
--         leds2 <= "0110000";
--   WHEN "1110" => leds1 <= "0110011"; -- 14
--         leds2 <= "0110000";
--   WHEN "1111" => leds1 <= "1011011"; -- 15
--         leds2 <= "0110000";
--   WHEN OTHERS => leds1 <= "-------"; -- idle
--         leds2 <= "-------";     
--  END CASE;
-- END PROCESS;
-- 
-- 
--END Behavior;

---- all?
--
--LIBRARY ieee;
--USE ieee.std_logic_1164.all;
--USE ieee.std_logic_unsigned.all;
--
--ENTITY lab_6 IS
--	PORT (setA, setB   						: IN STD_LOGIC_VECTOR(2 DOWNTO 0);
--		oper, addSub, action, clk			: IN STD_LOGIC;
--		viewComp   							: OUT STD_LOGIC_VECTOR(0 TO 1);
--		carry								: OUT STD_LOGIC;
--		A, B								: BUFFER STD_LOGIC_VECTOR(2 DOWNTO 0);
--		final								: OUT STD_LOGIC_VECTOR(2 DOWNTO 0));
--END lab_6;
--
--ARCHITECTURE Behavior of lab_6 IS
--
--	SIGNAL c0,c1,c2    : STD_LOGIC := '0';
--	SIGNAL diff		   : STD_LOGIC_VECTOR(0 TO 1);
--	SIGNAL rise_action : STD_LOGIC;
--		
--BEGIN
-- PROCESS(clk)
--	
--
-- VARIABLE resync_action 	: STD_LOGIC_VECTOR(2 DOWNTO 0) := "000";
-- 
--	BEGIN
--    IF (rising_edge(clk)) THEN
--     rise_action <= (NOT resync_action(2)) AND ( NOT resync_action(1)) AND ( resync_action(0));
--     resync_action:= NOT action & resync_action(2 DOWNTO 1);
--    END IF;
--    
--END PROCESS;
--
--	PROCESS (clk)
--	BEGIN
--	IF clk = '1' and clk'event then
--		
--		IF rise_action = '1' THEN
--			A <= setA;
--			B <= setB;
--		END IF;
--
--		IF (oper = '1') THEN
--			
--			IF (A(2) = B(2) AND A(1) = B(1) AND A(0) = B(0)) THEN
--					viewComp <= "11";
--			ELSIF ((A(2) = '1' AND B(2) = '0') OR (A(2) = '1' AND B(2) = '1' AND A(1) = '1' AND B(2) = '0') OR (A(2) = '1' AND B(2) = '1' AND A(1) = '1' AND B(1) = '1' AND A(0) = '1' AND B(0) = '0')) THEN
--				    viewComp <= "10";
--			ELSE
--					viewComp <= "01";
--			END IF;
--		END IF;
--	
--		IF (oper = '0') THEN
--			
--				IF (A(2) = B(2) AND A(1) = B(1) AND A(0) = B(0)) THEN
--						diff <= "11";
--				ELSIF ((A(2) = '1' AND B(2) = '0') OR (A(2) = '1' AND B(2) = '1' AND A(1) = '1' AND B(2) = '0') OR (A(2) = '1' AND B(2) = '1' AND A(1) = '1' AND B(1) = '1' AND A(0) = '1' AND B(0) = '0')) THEN
--						diff <= "10";
--				ELSE
--						diff <= "01";
--				END IF;
--			
--			IF (addSub = '1') THEN			
--				final(0) <= A(0) xor B(0); 
--				c0 <= A(0) and B(0); 
--				
--				final(1) <= A(1) xor B(1) xor c0;
--				c1 <= (A(1) and B(1)) or (A(1) and c0) or (B(1) and c0);
--
--				final(2) <= A(2) xor B(2) xor c1;
--				c2 <= (A(2) and B(2)) or (A(2) and c1) or (B(2) and c1);
--
--				carry <= c2;
--								
--			ELSIF (addSub = '0' AND diff = "11") THEN
--				carry <= '0';
--				final <= "000";
--			ELSIF (addsub = '0' AND diff = "10") THEN
--				carry <= '0';
--				final <= A - B;
--			ELSIF (addsub = '0' AND diff = "01") THEN
--				carry <= '0';
--				final <= B - A;
--			END IF;
--				
--		END IF;				
--	END IF;
--END PROCESS;
--END Behavior;

-- BCD to 7-segment decoder, outputs -7 to 7

--LIBRARY ieee;
--USE ieee.std_logic_1164.all;
--
--ENTITY lab_6 IS
--	PORT ( bcd  : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
--		   leds1 : OUT STD_LOGIC_VECTOR(1 TO 7);
--		   leds2 : OUT STD_LOGIC_VECTOR(1 TO 7);
--		   leds3 : OUT STD_LOGIC_VECTOR(1 TO 7);
--		   leds4 : OUT STD_LOGIC_VECTOR(1 TO 7));
--END lab_6;
--
--ARCHITECTURE Behavior OF lab_6 IS
--BEGIN
--	PROCESS(bcd)
--	BEGIN 
--		CASE bcd IS				 -- abcdefg
--			WHEN "0000"	=> leds1 <= "0000001"; -- 0
--						   leds2 <= "1111111";
--						   leds3 <= "1111111";
--						   leds4 <= "1111111";
--			WHEN "1000"	=> leds1 <= "0000001"; -- -0
--						   leds2 <= "1111111";
--						   leds3 <= "1111111";
--						   leds4 <= "1111111";
--			WHEN "0001"	=> leds1 <= "1001111"; -- 1
--						   leds2 <= "1111111";
--						   leds3 <= "1111111";
--						   leds4 <= "1111111";	
--			WHEN "1001"	=> leds1 <= "1001111"; -- -1
--						   leds2 <= "1111110";
--						   leds3 <= "1111111";
--						   leds4 <= "1111111";	
--			WHEN "0010"	=> leds1 <= "0010010"; -- 2 
--						   leds2 <= "1111111";
--						   leds3 <= "1111111";
--						   leds4 <= "1111111";
--			WHEN "1010"	=> leds1 <= "0010010"; -- -2 
--						   leds2 <= "1111110";
--						   leds3 <= "1111111";
--						   leds4 <= "1111111";		
--			WHEN "0011"	=> leds1 <= "0000110"; -- 3 
--						   leds2 <= "1111111";
--						   leds3 <= "1111111";
--						   leds4 <= "1111111";
--			WHEN "1011"	=> leds1 <= "0000110"; -- -3 
--						   leds2 <= "1111110";
--						   leds3 <= "1111111";
--						   leds4 <= "1111111";	
--			WHEN "0100"	=> leds1 <= "1001100"; -- 4 
--						   leds2 <= "1111111";
--						   leds3 <= "1111111";
--						   leds4 <= "1111111";	
--			WHEN "1100"	=> leds1 <= "1001100"; -- -4 
--						   leds2 <= "1111110";
--						   leds3 <= "1111111";
--						   leds4 <= "1111111";	
--			WHEN "0101"	=> leds1 <= "0100100"; -- 5 
--						   leds2 <= "1111111";
--						   leds3 <= "1111111";
--						   leds4 <= "1111111";
--			WHEN "1101"	=> leds1 <= "0100100"; -- -5 
--						   leds2 <= "1111110";
--						   leds3 <= "1111111";
--						   leds4 <= "1111111";	
--			WHEN "0110"	=> leds1 <= "0100000"; -- 6 
--						   leds2 <= "1111111";
--						   leds3 <= "1111111";
--						   leds4 <= "1111111";
--			WHEN "1110"	=> leds1 <= "0100000"; -- -6 
--						   leds2 <= "1111110";
--						   leds3 <= "1111111";
--						   leds4 <= "1111111";	
--			WHEN "0111"	=> leds1 <= "0001111"; -- 7
--						   leds2 <= "1111111";
--						   leds3 <= "1111111";
--						   leds4 <= "1111111";
--			WHEN "1111"	=> leds1 <= "0001111"; -- -7
--						   leds2 <= "1111110";
--						   leds3 <= "1111111";
--						   leds4 <= "1111111";	
----			WHEN "1000"	=> leds1 <= "0000000"; -- 8
----						   leds2 <= "1111111";
----						   leds3 <= "1111111";
----						   leds4 <= "1111111";	
----			WHEN "1001"	=> leds1 <= "0001100"; -- 9
----						   leds2 <= "1111111";
----						   leds3 <= "1111111";
----						   leds4 <= "1111111";	
----			WHEN "1010"	=> leds1 <= "0000001"; -- 10
----						   leds2 <= "1001111";
----						   leds3 <= "1111111";
----						   leds4 <= "1111111"; 
----			WHEN "1011"	=> leds1 <= "1001111"; -- 11
----						   leds2 <= "1001111";
----						   leds3 <= "1111111";
----						   leds4 <= "1111111";
----			WHEN "1100"	=> leds1 <= "0010010"; -- 12
----						   leds2 <= "1001111";
----						   leds3 <= "1111111";
----						   leds4 <= "1111111";
----			WHEN "1101"	=> leds1 <= "0000110"; -- 13
----						   leds2 <= "1001111";
----						   leds3 <= "1111111";
----						   leds4 <= "1111111";
----			WHEN "1110"	=> leds1 <= "1001100"; -- 14 
----						   leds2 <= "1001111";
----						   leds3 <= "1111111";
----						   leds4 <= "1111111";
----			WHEN "1111" => leds1 <= "0100100"; -- 15
----						   leds2 <= "1001111";
----						   leds3 <= "1111111";
----						   leds4 <= "1111111";
--			WHEN OTHERS => leds1 <= "-------"; -- idle
--						   leds2 <= "-------";					
--		END CASE;
--	END PROCESS;
--	
--	
-- END Behavior;