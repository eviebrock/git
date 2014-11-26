-- Notes on use:
-- Assumes active high logic for send and testWrite
-- Must keep send and testWrite high for multiple cycles
-- Modify the COMPONENT and PORT MAP to match your design

LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testBench IS 
 PORT(clk,send,testWrite   : IN STD_LOGIC;
   riseSend,devAView,devBView : OUT STD_LOGIC);
END testBench;

ARCHITECTURE Behavior OF testBench IS

 SIGNAL devBtest : STD_LOGIC := '0';
 SIGNAL busSignal : STD_LOGIC_VECTOR(3 DOWNTO 0);
 SIGNAL devAtest : STD_LOGIC;
 SIGNAL devA_BView : STD_LOGIC;
 
 -- REPLACE THIS WITH YOUR PORT DESCRIPTION
 COMPONENT lab_5 
  PORT(clkin, send, devB    : IN STD_LOGIC;
   devA       : BUFFER STD_LOGIC;
   riseSend, devAView, devBView : BUFFER STD_LOGIC);
 END COMPONENT;
 
BEGIN

 -- CONNECT YOUR PORTS HERE
 -- Ensure: devA is connected to devAtest, devB is connected to devBtest
 labConnect : lab_5 PORT MAP(clk,send,devBtest,devAtest,riseSend,devAView,devA_BView);
 
 -- This is the test logic for DevB; DO NOT MODIFY
 PROCESS(clk)
  VARIABLE resyncDevA : STD_LOGIC_VECTOR(2 DOWNTO 0) := "000";
 BEGIN
  IF(rising_edge(clk)) THEN
   -- synchronize devA signal
   resyncDevA := devAtest & resyncDevA(2 DOWNTO 1);
   
   -- mimic basic functionality of b side for testing
   IF(resyncDevA(1)='1' AND send='1' AND testWrite='0') THEN
    devBtest<='1';
   ELSIF(testWrite='1' AND resyncDevA(1)='0' AND send='0') THEN
    devBtest<='1';
   ELSIF(testWrite='1' AND resyncDevA(1)='1' AND send='0') THEN
    devBtest<='0';
   ELSE
    devBtest<='0';
   END IF;
  END IF;
 END PROCESS;
 
 devBView <= devBtest;
END Behavior;