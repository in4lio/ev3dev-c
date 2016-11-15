python -u ../yupp/yup.py -q -d../source/ev3 mainpage.yu-dox
rm ../html/*
rm -r ../html/search/
rem cp README.md ../html/
cp doxygen.log doxygen.log.bak
doxygen
