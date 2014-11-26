library ieee;
use ieee.std_logic_1164.all;

ENTITY lab_5 IS
    PORT(clkin, send, devB, reset       : IN STD_LOGIC;
  devA       : BUFFER STD_LOGIC;
  riseSend, devAView, devBView : BUFFER STD_LOGIC);
END lab_5;

ARCHITECTURE behavior OF lab_5 IS
    SIGNAL rise_send:std_logic;
    SIGNAL rise_devB:std_logic;
    SIGNAL SEND1:std_logic;
    SIGNAL SEND2:std_logic;
    SIGNAL DEVB1:std_logic;
    SIGNAL DEVB2:std_logic;
    SIGNAL fall_devB:std_logic;
    signal clocking: std_logic;
    
    component clk
  PORT ( iclk : IN STD_LOGIC;
   oclk: OUT STD_LOGIC);
  end component;

    Type state_type is (idle, s1, s2, recieve);
    signal y:state_type:=idle;

    BEGIN

 blah : clk port map (clkin, clocking);
 
    PROCESS(clocking)
    BEGIN
     IF(rising_edge(clocking)) THEN
          SEND1 <= not send;
          SEND2 <= SEND1;
          rise_send <= (NOT SEND2) AND SEND1;
          
          DEVB1 <= devB;
          DEVB2 <= DEVB1;
          rise_devB <= (NOT DEVB2) AND DEVB1;
          fall_devB <= DEVB2 AND (NOT DEVB1);

         case y is 
         
        when idle =>
   devA <= '0';
   
   if (rise_devB = '1') then
    y <= recieve;
   elsif(rise_send = '1') then
    y <= s1;
   elsif(reset = '1') then
    y <= idle;
      else
    y <= idle;
   end if;
   
  when s1 =>
   devA <= '1';
   
   if(rise_devB = '1') then
    y <= s2;
   elsif(reset = '1') then
    y <= idle;
   else
    y <= s1;
   end if;
   
  when s2 =>
   devA <= '0';
   
   if(fall_devB = '1') then
    y <= idle;
   elsif(reset = '1') then
    y <= idle;
   else
    y <= s2;
   end if;
   
  when recieve =>
   devA <= '1';
   
   if (fall_devB = '1') then 
    y <= idle;
   elsif(reset = '1') then
    y <= idle;
   else
    y <= recieve;
   end if;
   
   end case;

     END IF;

 END PROCESS;

 riseSend <= rise_send;
 devAView <= devA;
 devBView <= devB;

END behavior;