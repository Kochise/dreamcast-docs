--
-- Copyright (c) 2002 Kiyoshi Ikehara, Nagoya University Amateur Raido Club.
-- All rights reserved.
--
-- Redistribution and use in source and binary forms, with or without
-- modification, are permitted provided that the following conditions
-- are met:
--   1. Redistributions of source code must retain the above copyright
--      notice, this list of conditions and the following disclaimer.
--   2. Redistributions in binary form must reproduce the above copyright
--      notice, this list of conditions and the following disclaimer in the
--      documentation and/or other materials provided with the distribution.
--   3. All advertising materials mentioning features or use of this software
--      must display the following acknowledgement:
--        This product includes software developed by Nagoya University 
--        Amateur Raido Club and its contributors.
--   4. Neither the name of the Club nor the names of its contributors
--      may be used to endorse or promote products derived from this software
--      without specific prior written permission.
--

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity DCEXT is
	port(
	     DC_AD: inout std_logic_vector(15 downto 0);
	     DC_nEN: in std_logic;
	     DC_nDATEN: in std_logic;
	     DC_DIR: in std_logic;
	     DC_CLK: in std_logic;
	     DC_nINT: out std_logic;
	     ISA_A: out std_logic_vector(9 downto 0);
	     ISA_IRQ: in std_logic_vector(3 downto 0);
	     ISA_RST: out std_logic;
	     ISA_nRD: out std_logic;
	     ISA_nWD: out std_logic;
	     ISA_nG: out std_logic;
	     bufdir: out std_logic;
	     nRD: out std_logic;
	     nWD: out std_logic;
	     IDE_CS0: out std_logic;
	     IDE_CS1: out std_logic;
	     IDE_IRQ: in std_logic;
	     IDE_nRD: out std_logic;
	     IDE_nWD: out std_logic;
	     IDE_nG: out std_logic;
		  IDE_D: inout std_logic_vector(15 downto 0);
		  NC: out std_logic_vector(4 downto 0)
	);
end DCEXT;


architecture RTL of DCEXT is

signal A:        std_logic_vector(31 downto 0);
signal IRQ_CS:   std_logic;
signal ACS:      std_logic_vector(3 downto 0);
signal IRQSET:   std_logic_vector(4 downto 0);
signal ISA_CS:   std_logic;
signal IDE_CS:   std_logic;
signal TEST_CS0: std_logic;
signal TEST_CS1: std_logic;
signal RD, WD:   std_logic;
signal RD2, WD2: std_logic;
signal DIR:      std_logic;
signal DATAEN:   std_logic;
signal DCD:      std_logic_vector(15 downto 0);
signal MODE:     std_logic_vector(3 downto 0);
signal DRIVE:    std_logic;
signal ACTIVE:   std_logic;

constant ADDR_ISA:   std_logic_vector(3 downto 0) := "0000";
constant ADDR_IDE:   std_logic_vector(3 downto 0) := "0001";
constant ADDR_IRQ:   std_logic_vector(3 downto 0) := "1100";
constant ADDR_MODE:  std_logic_vector(3 downto 0) := "1111";

signal STATE:        std_logic_vector(1 downto 0);
signal NEXTSTATE:    std_logic_vector(1 downto 0);
signal IN_ADDRLOW:   std_logic;
signal IN_ADDRHIGH:  std_logic;
signal IN_DATALOW:   std_logic;
signal IN_DATAHIGH:  std_logic;
constant ADDRLOW:    std_logic_vector(1 downto 0) := "00";
constant ADDRHIGH:   std_logic_vector(1 downto 0) := "01";
constant DATALOW:    std_logic_vector(1 downto 0) := "11";
constant DATAHIGH:   std_logic_vector(1 downto 0) := "10";

begin
	
	-- tri-state
	ACTIVE <= '1' when A(31 downto 16) = X"1400" else '0';
	DRIVE <= DIR and IN_DATALOW and ACTIVE and (not ISA_CS);
	DC_AD <= DCD when DRIVE = '1' else (others => 'Z');

	-- "A" latch -> ISA address
	ISA_A <= A(11 downto 2);
	ACS <= A(15 downto 12);

	-- 
	IN_ADDRLOW   <= '1' when STATE = ADDRLOW  else '0';
	IN_ADDRHIGH  <= '1' when STATE = ADDRHIGH else '0';
	IN_DATALOW   <= '1' when STATE = DATALOW  else '0';
	IN_DATAHIGH  <= '1' when STATE = DATAHIGH else '0';

	-- irqs
	IRQSET <= (IDE_IRQ) & ISA_IRQ;

	-- interrupt
	DC_nINT <= '1' when (IRQSET = "00000") else '0';

	-- read / write
	RD <= DIR and (IN_ADDRHIGH or IN_DATALOW);
	WD <= (not DIR) and (IN_ADDRHIGH or IN_DATALOW);
	nRD <= not RD;
	nWD <= not WD;
	IDE_nRD <= not RD;
	IDE_nWD <= not WD;

	RD2 <= DIR and (IN_ADDRHIGH or IN_DATALOW);
	WD2 <= (not DIR) and (IN_ADDRHIGH or IN_DATALOW);
	ISA_nRD <= not (RD2 and ISA_CS); -- ISA_RD <= RD and ISA_CS
	ISA_nWD <= not (WD2 and ISA_CS); -- ISA_WD <= WD and ISA_CS

	-- bus EN
	DATAEN <= IN_DATALOW or IN_DATAHIGH;
	ISA_nG <= not (ISA_CS and DATAEN);
	bufdir <= not DIR;
	IDE_nG <= not (IDE_CS and IN_DATALOW); -- obsolete

	-- IDE data
	process(WD, ACS, DC_AD) begin
 		if(WD = '1' and IN_DATALOW = '1') then
			case ACS is
				when ADDR_IDE => IDE_D <= DC_AD;
				when others => IDE_D <= (others => 'Z');    -- not selected
			end case;
		else
			IDE_D <= (others => 'Z');
	   end if;
	end process;

	-- Clock
	process(DC_CLK) begin
		if(DC_CLK'event and DC_CLK='1') then
			STATE <= NEXTSTATE;
		end if;
	end process;

	-- State
	process(STATE, DC_CLK, ACS, DC_nEN, ACTIVE, IDE_D, IRQSET, MODE) begin
		case STATE is
			when ADDRLOW  =>
				if((DC_CLK'event and DC_CLK='0') and DC_nEN='0') then
					A(15 downto 0) <= DC_AD;
					DIR <= DC_DIR;
				end if;
				if(DC_nEN='0') then
						NEXTSTATE <= ADDRHIGH;
					else
						NEXTSTATE <= ADDRLOW;
				end if;
			when ADDRHIGH  =>						
				if(DC_CLK'event and DC_CLK='0') then
					A(31 downto 16) <= DC_AD;
				end if;
				NEXTSTATE <= DATALOW;
			when DATALOW  =>
				if(ACTIVE = '1') then
					case ACS is
						when ADDR_IDE  => DCD <= IDE_D;
						when ADDR_IRQ  => DCD <= X"00" & "000" & IRQSET; -- IRQ_CS
						when ADDR_MODE =>
							DCD <= X"000" & MODE;
							if((DC_CLK'event and DC_CLK='0') and DIR='0') then
								MODE <= DC_AD(3 downto 0);
							end if;
						when others    => DCD <= X"0000"; -- not selected
					end case;
				end if;
				NEXTSTATE <= DATAHIGH;
			when DATAHIGH  => 
				NEXTSTATE <= ADDRLOW;
			when others =>  NEXTSTATE <= ADDRLOW;
		end case;
	end process;

	-- CS -> each CS
	IDE_CS0 <= '0' when (ACS&A(11) = ADDR_IDE&'0') else '1';
	IDE_CS1 <= '0' when (ACS&A(11) = ADDR_IDE&'1') else '1';
	IDE_CS  <= '1' when ACS = ADDR_IDE else '0';
	ISA_CS  <= '1' when ACS = ADDR_ISA else '0';
	IRQ_CS  <= '1' when ACS = ADDR_IRQ else '0';

	ISA_RST <= MODE(0);

	NC <= (others => 'Z');

end RTL;


