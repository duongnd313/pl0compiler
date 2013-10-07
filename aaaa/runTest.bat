cls
@echo off
echo ***************************************************************************
echo *
echo *                           SYNTAX ANALYSER TEST
echo * 
echo * Course: Compiler Connstruction for HEDSPI 55
echo *
echo * Part 1: Normal syntax
echo * Part 2: Error syntax
echo * Part 3: Special syntax
echo *
echo * Syntax run:  runTest name[.exe]
echo **************************************************************************
 
rem @echo on 
echo ****************************************************************************
echo *                                   PART I: Normal syntax
echo ***************************************************************************

echo --> Khai bao don gian, khong co loi <--
%1 A1.PL0
pause


echo --> Khai bao phuctap, khong co loi <--
%1 A2.PL0 
Pause

echo --> Khai bao chuong trinh con, khong co loi <--
%1 A3.PL0 
Pause

echo --> Cau lenh don gian, khong co loi <--
%1 A4.PL0 
Pause

echo --> Bieu thuc don gian, khong co loi <--
%1 A5.PL0 
Pause


echo ****************************************************************************
echo *                                   PART II: syntax error
echo ***************************************************************************

echo -->Loi thieu toan tu; <--
%1 B1.PL0 
Pause

echo -->Loi thieu tu khoa do <--
%1 B2.PL0 
Pause

echo -->Loi thieu dong ngoac (o vi tri toan tu >) <--
%1 B3.PL0 
Pause

echo -->Loi thieu toan hang (o vi tri toan tu >) <--
%1 B4.PL0 
Pause

echo -->Thu tu Khai bao loi <--
%1 B5.PL0 
Pause

echo -->Khai bao loi <--
%1 B6.PL0 
Pause

echo -->Thieu toan tu gan <--
%1 B7.PL0 
Pause

echo -->Khai bao thu tuc loi <--
%1 B8.PL0 
Pause

echo -->Khai bao ham loi<--
%1 B9.PL0 
Pause

echo --> Chua co than chuong trinh <--
%1 B10.PL0 
Pause

echo ****************************************************************************
echo *                                   PART 3: Special syntax
echo ***************************************************************************

echo --> Bieu thuc dieu kien ? : <--
%1 C1.PL0 
Pause

echo -->Cau lenh REPEAT Staement [; Statement] UNTIL Condition <--
%1 C2.PL0 
Pause

echo --> Cau lenh FOR(Ident := Expression; Conditon; Ident := Expresion<--
%1 C3.PL0 
Pause

echo --> Do Statement [;Statement] WHILE (Condition) <--
%1 C4.PL0 
Pause

echo --> Cau lenh FOR Ident := Expression Downto Expression Do Statement<--
%1 C5.PL0 
Pause


