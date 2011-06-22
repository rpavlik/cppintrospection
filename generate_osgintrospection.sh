#!/bin/bash

# This script performs the applicable mechanical transformations to the
# source code and tree to allow easy comparison with the osgIntrospection
# library. It generates files in the "osgIntrospection_generated" directory.
# While the conversion is not entirely complete, it is sufficient to significantly
# reduce the noise when comparing with a diff tool.

function doConversion() {
	sed -e 's/cppintrospection/osgIntrospection/g' \
		-e 's/CPPINTROSPECTION/OSGINTROSPECTION/g' \
		-e 's/C[+][+] Introspection library/OpenSceneGraph Introspection library/' \
		-e 's/the Cpp Introspection library/the OpenSceneGraph (OSG) Introspection library/'
}

(
	cd "$(dirname $0)"
	out="osgIntrospection_generated"
	mkdir "$out" && (
		mkdir -p "$out/include/osgIntrospection"
		mkdir -p "$out/src/osgIntrospection"
		for fn in include/cppintrospection/*; do
			cat $fn | doConversion > "$out/include/osgIntrospection/$(basename $fn)"
		done
		for fn in src/cppintrospection/*.cpp; do
			cat $fn | doConversion > "$out/src/osgIntrospection/$(basename $fn)"
		done
	) || (
		echo "$out already exists - delete it before regenerating!" >2
		exit 1
	)
)
