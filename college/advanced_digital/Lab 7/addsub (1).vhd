LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_signed.all;
ENTITY addsub IS
	PORT (doAS : IN STD_LOGIC;
		  AS : IN STD_LOGIC;
		  OP,x	 : IN STD_LOGIC_VECTOR (2 downto 0);
		  y	 : IN STD_LOGIC_VECTOR (2 downto 0);
		  s	 : OUT STD_LOGIC_VECTOR (2 downto 0);
		  cout, overflow		  : OUT STD_LOGIC);
END addsub;
ARCHITECTURE Structure OF addsub IS
	Signal yAS : STD_LOGIC_VECTOR (2 downto 0);
	COMPONENT adder
		PORT (	doOP,cin		  	: IN STD_LOGIC;
				OP,x : IN STD_LOGIC_VECTOR (2 downto 0);
				y : IN STD_LOGIC_VECTOR (2 downto 0);
				s : OUT STD_LOGIC_VECTOR (2 downto 0);
				cout, overflow		  : OUT STD_LOGIC);
	END COMPONENT;
BEGIN 
		stage0:	adder PORT MAP(doAS,AS,OP,x,yAS,s,cout,overflow);
			yAS(0) <= y(0) xor AS; --since its 2 downto 0, LSB is 0
			yAS(1) <= y(1) xor AS;
			yAS(2) <= y(2) xor AS; --number representation is in signed decimal
								   --having # rep. in ASCII does not give correct results
								   --when incorrect output reached there is overflow	

END Structure;