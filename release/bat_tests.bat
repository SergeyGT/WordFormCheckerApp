set program=WordFormCheckerApp.exe

echo. > .\tests\results_all_tests.txt
echo 01 - Zero mistakes in sentence >> .\tests\results_all_tests.txt
%program% .\tests\incorrect_sentence_1.txt .\tests\correct_sentence_1.txt .\tests\output_1.txt >> .\tests\results_all_tests.txt
echo. >> .\tests\results_all_tests.txt

echo 02 - One mistake in sentence >> .\tests\results_all_tests.txt
%program% .\tests\incorrect_sentence_2.txt .\tests\correct_sentence_2.txt .\tests\output_2.txt >> .\tests\results_all_tests.txt
echo. >> .\tests\results_all_tests.txt

echo 03 - Two mistakes in sentence >> .\tests\results_all_tests.txt
%program% .\tests\incorrect_sentence_3.txt .\tests\correct_sentence_3.txt .\tests\output_3.txt >> .\tests\results_all_tests.txt
echo. >> .\tests\results_all_tests.txt

echo 04 - Mistake in every word >> .\tests\results_all_tests.txt
%program% .\tests\incorrect_sentence_4.txt .\tests\correct_sentence_4.txt .\tests\output_4.txt >> .\tests\results_all_tests.txt
echo. >> .\tests\results_all_tests.txt

echo 05 - Noun and Adjective mistake >> .\tests\results_all_tests.txt
%program% .\tests\incorrect_sentence_5.txt .\tests\correct_sentence_5.txt .\tests\output_5.txt >> .\tests\results_all_tests.txt
echo. >> .\tests\results_all_tests.txt

echo 06 - Noun and verb mistake >> .\tests\results_all_tests.txt
%program% .\tests\incorrect_sentence_6.txt .\tests\correct_sentence_6.txt .\tests\output_6.txt >> .\tests\results_all_tests.txt
echo. >> .\tests\results_all_tests.txt

echo 07 - Verb and number mistake >> .\tests\results_all_tests.txt
%program% .\tests\incorrect_sentence_7.txt .\tests\correct_sentence_7.txt .\tests\output_7.txt >> .\tests\results_all_tests.txt
echo. >> .\tests\results_all_tests.txt

echo 08 - Adjective and number mistake >> .\tests\results_all_tests.txt
%program% .\tests\incorrect_sentence_8.txt .\tests\correct_sentence_8.txt .\tests\output_8.txt >> .\tests\results_all_tests.txt
echo. >> .\tests\results_all_tests.txt

echo 09 - Mistake in number >> .\tests\results_all_tests.txt
%program% .\tests\incorrect_sentence_9.txt .\tests\correct_sentence_9.txt .\tests\output_9.txt >> .\tests\results_all_tests.txt
echo. >> .\tests\results_all_tests.txt

echo 10 - Mistake in adjective >> .\tests\results_all_tests.txt
%program% .\tests\incorrect_sentence_10.txt .\tests\correct_sentence_10.txt .\tests\output_10.txt >> .\tests\results_all_tests.txt
echo. >> .\tests\results_all_tests.txt

echo 11 - Complex test >> .\tests\results_all_tests.txt
%program% .\tests\incorrect_sentence_11.txt .\tests\correct_sentence_11.txt .\tests\output_11.txt >> .\tests\results_all_tests.txt
echo. >> .\tests\results_all_tests.txt

