echo "Note that you need to have the Boost autoconf macros"
echo "installed in order to autogen.  All of the autogen"
echo "dependencies are store in dependencies/m4 -- these"
echo "usually get put into /usr/share/aclocal"
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
