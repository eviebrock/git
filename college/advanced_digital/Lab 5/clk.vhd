LIBRARY ieee;
USE ieee.std_logic_1164.all;
-- Step down the 25.175MHz internal clock to get the desired freq:
-- choose the value XXXX to provide appropriate division
--
ENTITY clk IS
PORT ( iclk : IN STD_LOGIC;
oclk: OUT STD_LOGIC);
END clk;
ARCHITECTURE Behavior OF clk IS
SIGNAL Count: INTEGER RANGE 0 TO 13500000; --13500000
SIGNAL clkstate : STD_LOGIC;
BEGIN
PROCESS ( iclk )
BEGIN
IF (iclk'EVENT AND iclk = '1') THEN
IF Count = 13500000 THEN  --13500000 
Count <= 0;
clkstate <= not clkstate;
ELSE
Count <= Count + 1;
clkstate <= clkstate;
END IF;
END IF;
END PROCESS;
oclk <= clkstate;
END Behavior;