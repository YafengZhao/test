package com.glory.tests.analytics;

import java.io.File;
import java.util.Map;
import java.util.Map.Entry;
import java.util.HashMap;

import org.apache.spark.api.java.JavaPairRDD;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.sql.Dataset;
import org.apache.spark.sql.Row;
import org.apache.spark.sql.SparkSession;
import org.opengis.feature.simple.SimpleFeature;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.vividsolutions.jts.geom.Geometry;
import com.vividsolutions.jts.io.WKTReader;
import com.vividsolutions.jts.util.Stopwatch;

import javaslang.Function2;
import mil.nga.giat.geowave.analytic.spark.GeoWaveRDD;
import mil.nga.giat.geowave.analytic.spark.sparksql.SimpleFeatureDataFrame;
import mil.nga.giat.geowave.core.geotime.store.query.SpatialQuery;
import mil.nga.giat.geowave.core.store.operations.remote.options.DataStorePluginOptions;
import mil.nga.giat.geowave.core.store.operations.remote.options.StoreLoader;
import mil.nga.giat.geowave.mapreduce.input.GeoWaveInputKey;

/**
 * Hello world!
 *
 */
public class Analytics {
	private final static Logger LOGGER = LoggerFactory.getLogger(Analytics.class);

	private static final String GEOWAVECONF = "/home/ubuntu/.geowave/0.9.7-config.properties";

	protected DataStorePluginOptions dataStore;

	private static Stopwatch stopwatch = new Stopwatch();

	public Analytics() {
		// TODO Auto-generated constructor stub

		StoreLoader storeLoader = new StoreLoader("sparktest");
		storeLoader.loadFromConfig(new File(GEOWAVECONF));
		dataStore = storeLoader.getDataStorePlugin();
		System.out.println(dataStore.getOptionsAsMap());

	}

	public Analytics(String store) {

		StoreLoader storeLoader = new StoreLoader(store);
		storeLoader.loadFromConfig(new File(GEOWAVECONF));
		dataStore = storeLoader.getDataStorePlugin();
		System.out.println(dataStore.getOptionsAsMap());
	}

	public void runSql(String sql) throws Exception {

		WKTReader wktReader = new WKTReader();

		// DataAdapter dataAdapter = new DataAdapter(adapterId);

		SparkSession session = SparkSession.builder().master("local[*]").appName("SparkSql").getOrCreate();

		JavaSparkContext sparkContext = new JavaSparkContext(session.sparkContext());

		String rightBboxStr = "POLYGON ((-93.5 34, -92.5 34, -92.5 35, -93.5 35, -93.5 34))";
		Geometry rightBox = wktReader.read(rightBboxStr);
		SpatialQuery rightBoxQuery = new SpatialQuery(rightBox);

		JavaPairRDD<GeoWaveInputKey, SimpleFeature> rightRdd = GeoWaveRDD.rddForSimpleFeatures(sparkContext.sc(),
				dataStore, rightBoxQuery);
		
		/*
		rightRdd.reduceByKey(new Function2<String, String, String>() {
			public String call(String s1, String s2) {

				return s1 + s2;
			}
		});
		*/
		
		
		long total = rightRdd.count();
		LOGGER.info("=================all count: " + rightRdd.count() + "===========");
		
		LOGGER.info("==============================" + rightRdd.toString());
		
		/*
		java.util.Map<GeoWaveInputKey, SimpleFeature> map = rightRdd.collectAsMap();

		for(Entry<GeoWaveInputKey, SimpleFeature> entry: map.entrySet()) {
			
			LOGGER.info(entry.getKey().toString());
		}
		*/
		//LOGGER.info(map);
		// rightRdd.map(f)

		
		SimpleFeatureDataFrame rightDataFrame = new SimpleFeatureDataFrame(session);

		if (!rightDataFrame.init(dataStore, null)) {
			LOGGER.error("Failed to initialize dataframe");
		}

		Dataset<Row> results = rightDataFrame.getDataFrame(rightRdd);

		LOGGER.info("=================results count " + results.count() + "=======" + total);

		if (results.count() != 0) {

			results.show(20);
		}

		JavaRDD<Row> rowrdd = rightDataFrame.getRowRDD();
		
	}

	public static void main(String[] args) throws Exception {
		System.out.println("Hello World!");
		Analytics analytics = new Analytics("gdelt");
		// sparkTests.testCreateDataFrame();
		String sql = new String("select * from gdelt");
		analytics.runSql(sql);
	}
}
