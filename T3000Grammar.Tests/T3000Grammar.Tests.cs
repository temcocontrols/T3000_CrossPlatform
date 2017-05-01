﻿using System.Collections.Generic;

namespace T3000Grammar.Tests
{
    using System;
    using Irony.Parsing;
    using NUnit.Framework;

    [TestFixture]
    [Category("T3000Grammar")]
    public class T3000Grammar_Tests
    {
        public Dictionary<int, ParseTreeNode> ToDictionary(ParseTreeNode root)
        {
            var dictinary = new Dictionary<int, ParseTreeNode>();

            foreach (var child in root.ChildNodes)
            {
                var number = (int)child.ChildNodes.Find(i => i.Term.Name == "Number").Token.Value;
                var tree = child.ChildNodes.Find(i => i.Term.Name != "Number");

                dictinary.Add(number, tree);
            }

            return dictinary;
        }

        public void ShowTree(ParseTreeNode root)
        {
            foreach (var child in root.ChildNodes)
            {
                Console.WriteLine(child.ToString());
                if (child.ChildNodes.Count != 0)
                {
                    ShowTree(child);
                }
            }
        }

        [Test]
        public void BtuMeter_Lexer()
        {
            #region Test data

            var grammar = new T3000Grammar();
            var text = @"10 REM *********INITIALIZE THE TEST *************** 
20 IF TIME-ON ( INIT ) > 00:00:05 AND METERTOT < 1 THEN STOP INIT
30 REM ******** BTU METER ********** 
40 REM RESET THE FLOW METER TOTALIZER BY WRITING 1 TO REGISTER 136 
50 IF INIT THEN 19.253.REG136 = 1
60 REM GET FLOW TOTAL *** 
70 METER_HI = 19.253.REG132 / 1000
80 METER_LO = 19.253.REG131 / 1000
90 METERTOT = 65536 * METER_HI + METER_LO
100 REM READ THE METER TEMPS ************ 
110 BTUSUP = 19.253.REG108 / 10
120 BTURET = 19.253.REG107 / 10
130 REM ****** READ THE TANK1 WEIGH SCALE *************** 
140 IF INTERVAL ( 00:00:02 ) THEN WEIGHT = COM1 ( 9600 , 1 , 82 )
150 REM **************** WEIGHT READINGS ************** 
160 REM AT THE BEGINNING OF THE TEST, STORE THE WT IN STARTWT 
170 REM CONTINUOUSLY UPDATE THE ENDWT TO THE CURRENT WT 
180 REM AND AT THE END OF THE TEST, STORE THE ENDWT 
190 IF NOT SWITFLOW THEN ENDWT = WEIGHT
200 REM ******START THE COUNTERS AGAIN 
210 SCALETOT = SCALTOT2 + PUMPNOW
220 IF- SWITFLOW THEN STARTWT = WEIGHT
230 IF- SWITFLOW THEN SCALTOT2 = SCALETOT
240 REM ** IF INIT IS TRUE, KEEP THE PUMPS OFF FOR NOW ***** 
250 IF INIT THEN SCALTOT2 = 0
260 IF INIT THEN SCALETOT = 0
270 IF INIT THEN PUMPNOW = 0
280 IF INIT THEN STARTWT = WEIGHT
290 REM ************* MATH ************ 
300 IF NOT INIT THEN PUMPNOW = ABS ( WEIGHT - STARTWT )
310 IF INIT THEN PUMPNOW = 0
320 ERRORKG = SCALETOT - METERTOT
330 REM *** AT THE BEGINNING OF THE TEST, ERROR IS BIG, LIMIT TO SMALL VALUES 
340 IF INIT THEN ERRORKG = 0
350 IF METERTOT < 20 THEN ERRORKG = MAX ( -1 , MIN ( 1 , ERRORKG ) )
360 IF METERTOT > 20 THEN ERRORPCT = ERRORKG / METERTOT * 100 ELSE ERRORPCT = 0
370 REM *************BTU CALCS ************ 
380 DELTAT = ABS ( BTUSUP - BTURET )";

            #endregion

            var language = new LanguageData(grammar);
            var parser = new Parser(language);
            var tree = parser.Parse(text);
            var root = tree.Root;

            Assert.NotNull(root, "Parse tree unsuccessful");

            ShowTree(root);
            var dictionary = ToDictionary(root);

            Assert.AreEqual("IF-", dictionary[220].ChildNodes[0].ChildNodes[0].Token.Value);
        }
    }
}
