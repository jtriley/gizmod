echo
echo "Auto-generating configure and make..."
echo "libtoolizing..."
libtoolize --force
echo 
echo -n "running aclocal..."
aclocal
echo
echo -n "running automake..."
automake -a
echo
echo -n "running autoheader..."
autoheader
echo
echo -n "running autoconf..."
autoconf
echo
echo "Auto-generation complete."
echo
