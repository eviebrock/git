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