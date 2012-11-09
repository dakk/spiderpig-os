cp -R -u src/ /home/dak/svn/spiderpigos/trunk/
cp -R -u doc/ /home/dak/svn/spiderpigos/trunk/
cp -R -u image.iso /home/dak/svn/spiderpigos/trunk/
cp -R -u Makefile /home/dak/svn/spiderpigos/trunk/
cd ~/svn/spiderpigos/trunk

svn commit -m "$1"
