/*
 * =====================================================================================
 *
 *       Filename:  request.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018年06月22日 21时46分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhaoyafeng (), zhaoyafeng0615@163.com
 *   Organization:  GNU
 *
 * =====================================================================================
 */


#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <algorithm>
#include <vector>
#include <map>
#include <list>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>

#include <QtCore/QString>
#include <QtCore/QtDebug>
#include <QtCore/QFile>
#include <QtXml/QtXml>
#include <QtXml/QDomDocument>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>

using namespace curlpp::options;

std::string REQUEST_CONF = "./request_conf";


class features {

	class lable {

	public:
		std::string m_left_lable;
		std::string m_right_lable;
		std::string m_name;
		std::string m_value;

		lable(const std::string &left_lable, const std::string &right_lable):
			m_left_lable(left_lable),
			m_right_lable(right_lable) {

			}
	};


public:
	lable m_featureMember;
	lable m_geolifepoint;
	lable m_geometry;
	lable m_trackid;
	lable m_pointinstance;
	lable m_Timestamp;
	lable m_Latitude;
	lable m_Longitude;
	lable m_Elevation;

};


std::string getRequest(const std::string &conf)
{
	std::ifstream fs(conf.c_str(), std::ifstream::binary);

	if(fs.is_open() == false ) {

		return "";
	}

	fs.seekg(0, fs.end);

	long length = fs.tellg();

	fs.seekg(0, fs.beg);

	if(length == 0) {

		std::cerr << "Can not read " << conf << " file size is 0." << std::endl;
		fs.close();
		return "";
	}

	char *buffer = new char[length];

	fs.read(buffer, length);

	std::string temp_bf;

	temp_bf.assign(buffer, length);

	delete[] buffer;
	fs.close();
	return temp_bf;
}

std::string &trimRequest(std::string &dest, const std::string &src)
{


	std::vector<std::string> results;
	boost::algorithm::split(results, src, boost::is_any_of("\n"));

	BOOST_FOREACH(std::string &str, results) {

		dest += str;
		std::cout << str;
	}

	std::cout << std::endl;

	return dest;
}

long formatTimeToInt( const std::string &formatTime, const std::string format = ("%Y-%m-%d %H:%M:%S")) {

	std::locale lc = std::locale(std::locale::classic(),
			new boost::posix_time::time_input_facet(format));

	std::istringstream is(formatTime);
	is.imbue(lc);

	boost::posix_time::ptime pt;
	is >> pt;

	boost::posix_time::ptime timet_start(boost::gregorian::date(1970,1,1));
	boost::posix_time::time_duration diff = pt - timet_start;

	return diff.ticks()/boost::posix_time::time_duration::rep_type::ticks_per_second;
}

std::vector<std::map<std::string, std::string> > &parseXml(const std::string &src, 
		std::vector<std::map<std::string, std::string> >&results) {

	QDomDocument domdoc;

	QByteArray array(src.c_str(), src.size());

	domdoc.setContent(array);


	QDomNode root = domdoc.documentElement();
	qDebug() << "The root tag name is " << root.toElement().tagName();

	QDomNodeList childnodes = root.childNodes();

	for(int i = 0; i < childnodes.count(); i++) {

		qDebug() << childnodes.at(i).nodeName(); // book
		qDebug() << childnodes.at(i).toElement().attribute("category"); // <book category="children"> 

		QDomNode node = childnodes.at(i);

		for(int t = 0; t < node.childNodes().count(); t++ ) {

			QDomNode titleNode = node.childNodes().at(t);

			if(titleNode.nodeName().toStdString() == "geowave:geolifepoint") {


				std::map<std::string, std::string> attrs;
				for(int m = 0; m < titleNode.childNodes().count(); m++ ) {

					QDomNode subnode = titleNode.childNodes().at(m);

					std::string name = subnode.nodeName().toStdString();
					std::string value = subnode.firstChild().nodeValue().toStdString();
					std::cout << "=======" << name << "::" << value << std::endl;

					attrs.insert(std::pair<std::string, std::string>(name, value));

				}
				results.push_back(attrs);
			}
		}

	}
}

std::vector<std::map<std::string, std::string> > &parseGeolifeFile(
		const std::string &file, std::vector<std::map<std::string, std::string> > &results )
{

	std::ifstream fs(file.c_str(), std::ios::binary);

	if(fs.is_open()  == false ) {

		return results;
	}

	bool isstart = false;

	enum {Latitude=0, Longitude=1, Elevation=3, ymd=5, hms=6};
	for(std::string line; std::getline(fs, line); ) {

		if(isstart == false) {

			if(line.size() == 2 && line[0] == '0') {

				isstart = true;
			} 

				continue;
		}

		std::vector<std::string> values;
		boost::algorithm::split(values, line, boost::is_any_of(","));

		std::map<std::string, std::string> attrs;

//		std::cout << boost::filesystem::absolute(file) << "====" << std::endl;
		attrs.insert(std::pair<std::string, std::string>("trackid", file));

		attrs.insert(std::pair<std::string, std::string>("Latitude", values.at(Latitude)));

		attrs.insert(std::pair<std::string, std::string>("Longitude", values.at(Longitude)));
	
		attrs.insert(std::pair<std::string, std::string>("Elevation", values.at(Elevation)));

		attrs.insert(std::pair<std::string, std::string>("Timestamp", values.at(ymd) + "T" + values.at(hms)));


		results.push_back(attrs);

	}

	return results;
}

int main(void)
{

	try{

		std::ostringstream os;


		std::string request = "http://127.0.0.1:8888/geoserver/geowave/ows?service=WFS&version=1.0.0&request=GetFeature&typeName=geowave:geolifepoint&maxFeatures=2&Filter=<Filter><PropertyIsLessThan><PropertyName>Timestamp</PropertyName><Literal>2008-10-23T02:55:25</Literal></PropertyIsLessThan></Filter>";
		std::cout << request << std::endl;

		curlpp::Cleanup myCleanup;

		os << curlpp::options::Url(request);

		std::cout << os.str() << std::endl;

		std::vector<std::map<std::string, std::string> > results;
		parseXml(os.str(), results);

		std::cout << results.size() << std::endl;


		std::string timeFormat("%Y-%m-%dT%H:%M:%S");
		std::string formatTime("2008-10-23T02:53:10");

		std::cout << formatTimeToInt(formatTime, timeFormat) << std::endl;


		std::string geoLief("./v1/20081023025304.plt");
		std::vector<std::map<std::string, std::string> > geolifes;

		
		parseGeolifeFile(geoLief, geolifes);

		std::vector<std::map<std::string, std::string> >::iterator it = geolifes.begin();

		//for(; it != geolifes.end(); it++) {

		//	std::cout << (*it)["trackid"] << std::endl;
		//}

	} catch (std::exception e) {

		std::cout << e.what() << std::endl;
	}

	return 0;
}
