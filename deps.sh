#! /bin/sh

BASE=`pwd`


function git_dep() {
	DEPNAME=$1
	REPO=$2
	
	DEP=${BASE}/${DEPNAME}
	if [ -d "${DEP}/.git" ]; then
		echo "Updating ${DEPNAME}"
		cd "${DEP}"
		git pull
		cd "${BASE}"
	else
		echo "Checking out ${DEPNAME}"
		rm -fr "${DEP}"
		git clone "${REPO}" "${DEP}"
	fi
}

function darcs_dep() {
	DEPNAME=$1
	REPO=$2
	
	DEP=${BASE}/${DEPNAME}
	if [ -d "${DEP}/_darcs" ]; then
		echo "Updating ${DEPNAME}"
		cd "${DEP}"
		darcs pull -a
		cd "${BASE}"
	else
		echo "Checking out ${DEPNAME}"
		rm -fr "${DEP}"
		darcs get --lazy "${REPO}" "${DEP}"
	fi
}

function http_zip_dep() {
	DEPNAME=$1
	REPO=$2
	
	DEP=${BASE}/${DEPNAME}
	TMP=${DEP}.tmp.zip
	if [ -d "${DEP}" ]; then
		echo "${DEPNAME} already present"
	else
		echo "Checking out ${DEPNAME}"
		mkdir -p "${DEP}"
		cd "${DEP}"
		wget -O "${TMP}" "${REPO}"
		unzip "${TMP}"
		rm -fr "${TMP}"
	fi
}


echo "Setting up dependencies in ${BASE}"

darcs_dep GF http://www.grammaticalframework.org/
git_dep JPGF https://github.com/GrammaticalFramework/JPGF.git
git_dep PhraseDroid https://github.com/GrammaticalFramework/PhraseDroid.git
http_zip_dep gtest http://googletest.googlecode.com/files/gtest-1.6.0.zip
