python -u ../yupp/yup.py --pp-no-skip-c-comment -q -d../source/ev3 mainpage.yu-dox
rm ../html/*
rm -r ../html/search/
cp README ../html/
doxygen
