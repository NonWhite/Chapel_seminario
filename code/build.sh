CURRENT="$(pwd)"
echo $CURRENT

cd $HOME/chapel
. util/setchplenv.sh

make

make check

cd "$CURRENT"
