geonames: geonames.c
	gcc -o geonames -std=c11 -Wall -Wextra geonames.c

html: README.md sujet.md 
	pandoc --metadata pagetitle="README" -f markdown-yaml_metadata_block -s -c ./misc/github-pandoc.css "README.md" -o "README.html"
	pandoc --metadata pagetitle="sujet" -f markdown-yaml_metadata_block -s -c ./misc/github-pandoc.css "sujet.md" -o "sujet.html" 
 

database: 
	curl http://download.geonames.org/export/dump/countryInfo.txt --output countryInfo.txt
	curl http://download.geonames.org/export/dump/cities15000.zip --output cities15000.zip
	unzip cities15000.zip
	rm cities15000.zip

test: geonames 
	bats check.bats

clean: 
	rm "cities15000.txt"
	rm "countryInfo.txt"
	rm *.html
	rm *.o


