-- hds header_start
--
-- VHDL Entity DigAlarm.BCDDecoder.interface
--
-- Created:
--          by - Hawley001.UNKNOWN (Z314ECEPC11)
--          at - 21:03:07 12/05/02
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2001.1 (Build 12)
--
-- hds header_end
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;


ENTITY BCDDecoder IS
   PORT( 
      Clock        : IN     std_logic;
      DisplayClock : IN     std_logic_vector (7 DOWNTO 0);
      SEG          : IN     std_logic_vector (3 DOWNTO 0);
      display      : OUT    std_logic_vector (6 DOWNTO 0)
   );

-- Declarations

END BCDDecoder ;

-- hds interface_end
--
-- VHDL Architecture DigAlarm.BCDDecoder.tbl
--
-- Created:
--          by - Hawley001.UNKNOWN (Z314ECEPC11)
--          at - 21:03:07 12/05/02
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2001.1 (Build 12)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

ARCHITECTURE tbl OF BCDDecoder IS
   
      -- Architecture declarations
    

BEGIN

   ---------------------------------------------------------------------------
   truth_process: PROCESS(SEG)
   ---------------------------------------------------------------------------
   BEGIN
      -- Block 1
      IF (SEG = "0000") THEN
         display <= "1111110";
      ELSIF (SEG = "0001") THEN
         display <= "0110000";
      ELSIF (SEG = "0010") THEN
         display <= "1101101";
      ELSIF (SEG = "0011") THEN
         display <= "1111001";
      ELSIF (SEG = "0100") THEN
         display <= "0110011";
      ELSIF (SEG = "0101") THEN
         display <= "1011011";
      ELSIF (SEG = "0110") THEN
         display <= "1011111";
      ELSIF (SEG = "0111") THEN
         display <= "1110000";
      ELSIF (SEG = "1000") THEN
         display <= "1111111";
      ELSIF (SEG = "1001") THEN
         display <= "1110011";
      END IF;

   END PROCESS truth_process;

-- Architecture concurrent statements
 

END tbl;
