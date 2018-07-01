package com.glory.test.analytic

import mil.nga.giat.geowave.adapter.vector._
import mil.nga.giat.geowave.core.geotime.ingest._
import mil.nga.giat.geowave.core.{store => geowave}
import mil.nga.giat.geowave.core.store.index._
import mil.nga.giat.geowave.datastore.hbase._
import mil.nga.giat.geowave.datastore.hbase.index.secondary._                                                                                                                                                                                                                                                                                     
import mil.nga.giat.geowave.datastore.hbase.metadata._
import mil.nga.giat.geowave.datastore.hbase.operations.config.HBaseOptions
import org.geotools.data.{DataStoreFinder, FeatureSource}
import org.geotools.feature.FeatureCollection
import org.opengis.filter.Filter
import org.opengis.feature.simple.{SimpleFeature, SimpleFeatureType}
import org.geotools.data.simple.SimpleFeatureStore
import org.apache.spark.{SparkConf, SparkContext}
import org.apache.spark.rdd._
import mil.nga.giat.geowave.core.store.operations.remote.options.DataStorePluginOptions;
import mil.nga.giat.geowave.core.store.operations.remote.options.StoreLoader;
import mil.nga.giat.geowave.datastore.hbase.util.ConnectionPool;
import mil.nga.giat.geowave.datastore.hbase.operations.BasicHBaseOperations;
import mil.nga.giat.geowave.core.geotime.store.query.SpatialQuery;

import mil.nga.giat.geowave.analytic.spark.GeoWaveRDD;
import mil.nga.giat.geowave.analytic.spark.sparksql.SimpleFeatureDataFrame;

import org.apache.spark.api.java.JavaPairRDD;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.sql.Dataset;
import org.apache.spark.sql.Row;

import com.vividsolutions.jts.geom.Geometry;
import com.vividsolutions.jts.io.WKTReader;
import com.vividsolutions.jts.util.Stopwatch;

import java.io.File;
import java.util.HashMap
import scala.collection.JavaConversions._
import scala.util.Try
import org.apache.spark.SparkConf
import org.apache.spark.SparkConf
import org.apache.spark.sql.SparkSession


/**
 * @author ${user.name}
 */
object SparkAnalytic {
  
  
  def main(args : Array[String]) {
    println( "Hello World!" )
    
    val conf: SparkConf = new SparkConf().setAppName("SparkTests");
    
    val sparkSession = SparkSession.builder().config(conf).master("local").getOrCreate();
    val sparkContext  = sparkSession.sparkContext;

    val GEOWAVECONF = "/home/ubuntu/.geowave/0.9.7-config.properties";
    
    val storename = "gdelt";
    val storeLoader = new StoreLoader(storename);
		storeLoader.loadFromConfig(new File(GEOWAVECONF));
		val storeOptions = storeLoader.getDataStorePlugin();
		
		//println(dataStore.getOptionsAsMap());
    
    /*
    val zookeeper = "shineassun:2181";
    val namespace = "geowave.geolife-temporal";
    val connectionPool = ConnectionPool.getInstance();
    val connection = connectionPool.getConnection(zookeeper);

    val storeOptions = new BasicHBaseOperations(connection, namespace);
    val datastore = new HBaseDataStore(storeOptions);
    */
    
    val wktReader = new WKTReader();

    //val rightBboxStr = "POLYGON ((-93.5 34, -92.5 34, -92.5 35, -93.5 35, -93.5 34))";
        val rightBboxStr = "POLYGON ((-180 -90, -180 90, 180 90, 180 -90, -180 -90))";
		val rightBox = wktReader.read(rightBboxStr);
		val rightBoxQuery = new SpatialQuery(rightBox);
		
		val rightRdd = GeoWaveRDD.rddForSimpleFeatures(sparkContext,
				storeOptions, rightBoxQuery);
		
		val rightDataFrame = new SimpleFeatureDataFrame(sparkSession);

		if (!rightDataFrame.init(storeOptions, null)) {
			println("Failed to initialize dataframe");
		}
		
		val results  = rightDataFrame.getDataFrame(rightRdd);

		//println("=================results count " + results.count() + "=======");
		
	//	results.createOrReplaceTempView(storename);
		
	//	val sqlText = "select * from gdelt";
	//	val sqlresult = sparkSession.sql(sqlText);
		
	//	sqlresult.show(20);
		
		val rowrdd = rightDataFrame.getRowRDD();
		
		/*
		val maprdd = rowrdd.map(new org.apache.spark.api.java.function.Function[Row, Tuple2[String, String] ]() {
		  
		  override def call(r :Row):  Tuple2[String, String] = (r.getString(7) + " " + r.getString(8), r.getString(0))
		})
		* */
		
		//rowrdd.filter((r :org.apache.spark.sql.Row) => r.getBoolean(1))
		//val maprdd = rowrdd.map((r :org.apache.spark.sql.Row)  => (r.getString(7) + " " + r.getString(8), r));
		//val maprdd = rowrdd.map { r :org.apache.spark.sql.Row => r};

		val maprdd = rowrdd.keyBy(new org.apache.spark.api.java.function.Function[Row, String]() {
		  
		  override def call(r :Row): String = r.getString(7) + " " + r.getString(8)
		})
		
		val groups = maprdd.aggregateByKey(List(), new org.apache.spark.api.java.function.Function2[List[Row], Row, List[Row]]() {
		  
		  override def call(l :List[Row], r :Row): List[Row] = l :+ r 
		}, 
		    new org.apache.spark.api.java.function.Function2[List[Row], List[Row], List[Row]]() {
		  override def call(l1 :List[Row], l2 :List[Row]): List[Row] = l1 ::: l2
		})
		
		groups.foreach(new org.apache.spark.api.java.function.VoidFunction[(String, List[Row])]() {
		  
		  override def call(t: (String, List[Row])): Unit = println(t)
		})
		
	//	groups.saveAsTextFile("/tmp/123")
		
		println("----------------------------")
		//println(groups.first() + "================");
		sparkSession.close();
  }

}
