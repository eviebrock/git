LIBRARY ieee; 
USE ieee.std_logic_1164.all;
ENTITY fulladd IS
	PORT (doOP,cin, x, y : IN STD_LOGIC;
			  OP : IN STD_LOGIC_VECTOR (2 downto 0);
			  s, cout: OUT STD_LOGIC);
END fulladd;
ARCHITECTURE LogicFunc OF fulladd IS
BEGIN 
	
	
	s <= (x xor y xor cin) when (doOP = '1' AND (OP = "000" OR OP = "001") ) else '0';
	cout <= ((x and y) or (cin and x) or (cin and y)) when (doOP = '1' AND (OP = "000" OR OP = "001") ) else '0';
	
END LogicFunc;