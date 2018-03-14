/*
 * =====================================================================================
 *
 *       Filename:  parseXml.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/14/2018 02:07:39 PM
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

#include <QtCore/QString>
#include <QtCore/QtDebug>
#include <QtCore/QFile>
#include <QtXml/QtXml>
#include <QtXml/QDomDocument>


int main(void)
{
	QFile xml("./test.xml");
	xml.open(QIODevice::ReadOnly);
	if(xml.isOpen() == false) {

		qDebug() << "Open xml failed.";
		return -1;
	}

	QDomDocument domdoc;
	domdoc.setContent(xml.readAll());

	xml.close();

	QDomNode root = domdoc.documentElement();
	qDebug() << "The root tag name is " << root.toElement().tagName();

	QDomNodeList childnodes = root.childNodes();
	qDebug() << childnodes.count(); // 4 childnodes

	for(int i = 0; i < childnodes.count(); i++) {

		qDebug() << childnodes.at(i).nodeName(); // book
		qDebug() << childnodes.at(i).toElement().attribute("category"); // <book category="children"> 

	}

	// parse this part
	/*
	<book category="children">
		<title lang="en">harry potter</title> 
		<author>j k. rowling</author> 
		<year>2005</year> 
		<price>29.99</price> 
	</book>
	*/

	QDomNode node = childnodes.at(0);
	qDebug() << node.childNodes().count(); // 4

	// title node
	QDomNode titleNode = node.childNodes().at(0);
	qDebug() << titleNode.nodeName(); // title
	qDebug() << titleNode.toElement().tagName(); // title 
	qDebug() << titleNode.toElement().nodeValue(); // harry potter is not the node value
	qDebug() << titleNode.firstChild().nodeValue(); // harry potter is the value of tiltle node  
	qDebug() << titleNode.firstChild().isText(); // harry potter is text

	return 0;
}
