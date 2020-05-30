#!/bin/bash

TEMPLATE_LOCATION=$HOME/Projects/cppnew/templates

TEMPLATE=$1
DIR_NAME=$2

function list_templates() {

for f in ${TEMPLATE_LOCATION}/*; do
    if [ -f ${f}/DESCRIPTION ]; then
        # Will not run if no directories are available
        echo "   " $(basename ${f} suffix)  -  $(cat ${f}/DESCRIPTION)
    fi
done

}


function new_proj() {
   template=$1
}

function template_exists()
{
    if [[ -f ${TEMPLATE_LOCATION}/$1/DESCRIPTION ]]; then 
        return 0
    fi
    return 1
}

if [[ "$TEMPLATE" == "" || "$DIR_NAME" == "" ]]; then
echo ""
echo "Templates:"
echo ""
list_templates
exit 1
fi

if [ -e ${PWD}/${DIR_NAME} ]; then 
    echo ${PWD}/${DIR_NAME} exists. Cannot create template
    exit 1
fi


if [[ "$TEMPLATE" == "" || "$DIR_NAME" == "" ]]; then

list_templates

else

    if ! template_exists $TEMPLATE; then

        echo "Template, ${TEMPLATE} does not exist"

    else

        cp  -r ${TEMPLATE_LOCATION}/$1 ${DIR_NAME}
        rm  ${TEMPLATE_LOCATION}/$1/DESCRIPTION

    fi    

fi


