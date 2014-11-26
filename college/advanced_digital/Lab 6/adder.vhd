-- adder

LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_signed.all;
ENTITY adder IS
	PORT (doOP,cin		  : IN STD_LOGIC;
		  OP,x : IN STD_LOGIC_VECTOR (2 downto 0);
		  y : IN STD_LOGIC_VECTOR (2 downto 0);
		  s : OUT STD_LOGIC_VECTOR (2 downto 0);
		  cout, overflow		  : OUT STD_LOGIC);
END adder;
ARCHITECTURE Structure OF adder IS
	SIGNAL c1,c2,c3,c4 : STD_LOGIC;
	COMPONENT fulladd
		PORT (doOP,cin, x, y : IN STD_LOGIC;
			  OP : IN STD_LOGIC_VECTOR (2 downto 0);
			  s, cout: OUT STD_LOGIC);
	END COMPONENT;
BEGIN 
	stage0: fulladd PORT MAP(doOP,cin, x(0), y(0),OP, s(0), c1);
	stage1: fulladd PORT MAP(doOP,c1, x(1), y(1),OP, s(1), c2);
	stage2: fulladd PORT MAP(doOP,c2, x(2), y(2),OP, s(2), c3);

			cout<= c3; 
			overflow <= (c2 xor c3);
END Structure;