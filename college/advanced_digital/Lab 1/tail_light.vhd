LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY tail_light IS
	PORT ( L, R, H, Clock	:IN STD_LOGIC;
		   Lights			:buffer STD_LOGIC_VECTOR (1 to 6));
END tail_light;

ARCHITECTURE Behavior OF tail_light IS
	TYPE State_type IS (off, LA, LB, LC, RA, RB, RC, LR);
	SIGNAL y: State_type;
BEGIN
	PROCESS (Clock, H, L, R)
	BEGIN
		IF H = '1' THEN
			y <= off;
		ELSIF clock = '0' THEN
			y <= off;
		ELSIF (Clock'EVENT AND Clock = '1') THEN
			CASE y IS
				WHEN off =>
					IF H = '1' THEN y <= LR;
					ELSIF L = '1' THEN y <= LA;
					ELSIF R = '1' THEN Y <= RA;
					ELSE y <= off;
					END IF;
				WHEN LA =>
					IF H = '1' then y <= LR;
					ELSE y <= LB;
					END IF;
				WHEN LB =>
					IF H = '1' then y <= LR;
					ELSE y <= LC;
					END IF;
				WHEN LC =>
					y <= off;
				WHEN RA =>
					IF H = '1' then y <= LR;
					ELSE y <= RB;
					END IF;
				WHEN RB =>
					IF H = '1' then y <= LR;
					ELSE y <= RC;
					END IF;
				WHEN RC =>
					y <= off;
				WHEN LR =>
					y <= off;
			END CASE;
		END IF;
	END PROCESS;
PROCESS (Lights, y)
BEGIN
IF
		y = off
			THEN Lights <= "000000";
ElSIF
		y = LR
			THEN Lights <= "111111";
ElSIF
		y = LA			
			THEN Lights <= "010000";
ElSIF
		y = LB
			THEN Lights <= "101000";
ElSIF
		y = LC
			THEN Lights <= "111000";
ElSIF
		y = RA
			THEN Lights <= "000010";
ElSIF
		y = RB
			THEN Lights <= "000101";
ElSIF
		y = RC
			THEN Lights <= "000111";
END IF;
END PROCESS;
END Behavior;
