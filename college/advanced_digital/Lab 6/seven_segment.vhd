-- seven segment

LIBRARY ieee;
USE ieee.std_logic_1164.all;
 
ENTITY sevensegment IS
 PORT ( Adisplay, Bdisplay, OPdisplay,ResultDisplay   : IN STD_LOGIC_VECTOR(2 DOWNTO 0); -- ResultDisplay
  leds1, leds2, leds3, leds4     : OUT STD_LOGIC_VECTOR(1 TO 7);
   posneg1, posneg2, posneg3  : OUT STD_LOGIC);

END sevensegment;

ARCHITECTURE Behavior OF sevensegment IS
BEGIN
 PROCESS(Adisplay, Bdisplay, OPdisplay,ResultDisplay ) -- ResultDisplay
 BEGIN 
  CASE Adisplay IS    -- abcdefg
    WHEN "000" => leds1  <= "0000001"; -- 0
        posneg1 <= '0';
   WHEN "001" => leds1 <= "1001111"; -- 1
        posneg1 <= '0'; 
    WHEN "111" => leds1 <= "1001111"; -- -1
         posneg1 <= '1'; 
   WHEN "010" => leds1 <= "0010010"; -- 2 
        posneg1 <= '0';
   WHEN "110" => leds1 <= "0010010"; -- -2 
        posneg1 <= '1';  
   WHEN "011" => leds1 <= "0000110"; -- 3 
        posneg1 <= '0';
   WHEN "101" => leds1 <= "0000110"; -- -3 
        posneg1 <= '1'; 
   WHEN "100" => leds1 <= "1001100"; -- -4 
        posneg1 <= '1';     
   WHEN OTHERS => leds1 <= "-------"; -- idle
         posneg1 <= '0'; 
  END CASE;
  CASE Bdisplay IS    -- abcdefg
   WHEN "000" => leds2  <= "0000001"; -- 0
        posneg2 <= '0';
   WHEN "001" => leds2 <= "1001111"; -- 1
         posneg2 <= '0'; 
   WHEN "111" => leds2 <= "1001111"; -- -1
        posneg2 <= '1'; 
   WHEN "010" => leds2 <= "0010010"; -- 2 
        posneg2 <= '0';
   WHEN "110" => leds2 <= "0010010"; -- -2 
        posneg2 <= '1';  
   WHEN "011" => leds2 <= "0000110"; -- 3 
        posneg2 <= '0';
   WHEN "101" => leds2 <= "0000110"; -- -3 
        posneg2 <= '1'; 
   WHEN "100" => leds2 <= "1001100"; -- -4 
        posneg2 <= '1';     
   WHEN OTHERS => leds2 <= "-------"; -- idle
        posneg2 <= '0'; 
  END CASE;
  CASE OPdisplay IS    -- abcdefg
   WHEN "000" => leds3  <= "0000001"; -- 0, add
    WHEN "001" => leds3 <= "1001111"; -- 1, subtract
   WHEN "100" => leds3 <= "0010010"; -- 2, equal 
   WHEN "101" => leds3 <= "0000110"; -- 3, greater than 
   WHEN "110" => leds3 <= "1001100"; -- 4, less than
   WHEN "111" => leds3 <= "0100100"; -- 5, a = 0
   WHEN OTHERS => leds3 <= "1111111"; -- idle
   END CASE;
  CASE ResultDisplay IS     -- abcdefg
   WHEN "000" => leds4  <= "0000001"; -- 0
        posneg3 <= '0';
   WHEN "001" => leds4 <= "1001111"; -- 1
        posneg3 <= '0'; 
   WHEN "111" => leds4 <= "1001111"; -- -1
        posneg3 <= '1'; 
   WHEN "010" => leds4 <= "0010010"; -- 2 
        posneg3 <= '0';
   WHEN "110" => leds4 <= "0010010"; -- -2 
        posneg3 <= '1';  
   WHEN "011" => leds4 <= "0000110"; -- 3 
        posneg3 <= '0';
   WHEN "101" => leds4 <= "0000110"; -- -3 
        posneg3 <= '1'; 
   WHEN "100" => leds4 <= "1001100"; -- -4 
        posneg3 <= '1';     
   WHEN OTHERS => leds4 <= "-------"; -- idle
        posneg3 <= '0'; 
  END CASE;
 END PROCESS;
END Behavior;
 
