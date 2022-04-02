gcc micro_paint.c -o nooriginal -Wall -Wextra -Werror
gcc our_micro_paint.c -o original -Wall -Wextra -Werror
echo ""
echo "TEST - <ex_1>"
echo "NO original"
./nooriginal ./examples/ex_1
echo "Original"
./original ./examples/ex_1
echo ""
echo "TEST - <ex_2>"
echo "NO original"
./nooriginal ./examples/ex_2
echo "Original"
./original ./examples/ex_2
echo ""
echo "TEST - <ex_3>"
echo "NO original"
./nooriginal ./examples/ex_3
echo "Original"
./original ./examples/ex_3
echo ""
echo "TEST - <ex_4>"
echo "NO original"
./nooriginal ./examples/ex_4
echo "Original"
./original ./examples/ex_4
echo ""
echo "TEST - <NULL>"
echo "NO original"
./nooriginal
echo "Original"
./original
echo ""
echo "TEST - <Error file>"
echo "NO original"
./nooriginal ./examples/ex
echo "Original"
./original ./examples/ex
echo ""
echo "TEST - <Additional_1>"
echo "NO original"
./nooriginal ./examples/1
echo "Original"
./original ./examples/1
echo ""
echo "TEST - <Additional_2>"
echo "NO original"
./nooriginal ./examples/2
echo "Original"
./original ./examples/2
echo ""
echo "TEST - <Additional_3>"
echo "NO original"
./nooriginal ./examples/3
echo "Original"
./original ./examples/3
echo ""
echo "TEST - <Additional_4>"
echo "NO original"
./nooriginal ./examples/4
echo "Original"
./original ./examples/4
echo ""
echo "TEST - <Additional_5>"
echo "NO original"
./nooriginal ./examples/5
echo "Original"
./original ./examples/5
echo ""
echo "TEST - <Additional_6>"
echo "NO original"
./nooriginal ./examples/6
echo "Original"
./original ./examples/6
echo ""
echo "TEST - <Additional_7>"
echo "NO original"
./nooriginal ./examples/7
echo "Original"
./original ./examples/7
echo ""
echo "TEST - <Additional_8>"
echo "NO original"
./nooriginal ./examples/8
echo "Original"
./original ./examples/8
rm nooriginal
rm original