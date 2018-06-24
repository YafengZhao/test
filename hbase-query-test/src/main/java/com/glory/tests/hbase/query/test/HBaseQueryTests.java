package com.glory.tests.hbase.query.test;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.apache.hadoop.hbase.client.Connection;
import org.opengis.feature.simple.SimpleFeature;

import com.vividsolutions.jts.geom.Coordinate;

import mil.nga.giat.geowave.core.geotime.GeometryUtils;
import mil.nga.giat.geowave.core.geotime.store.filter.SpatialQueryFilter.CompareOperation;
import mil.nga.giat.geowave.core.geotime.store.query.SpatialTemporalQuery;
import mil.nga.giat.geowave.core.store.CloseableIterator;
import mil.nga.giat.geowave.core.store.query.QueryOptions;
import mil.nga.giat.geowave.datastore.hbase.HBaseDataStore;
import mil.nga.giat.geowave.datastore.hbase.operations.BasicHBaseOperations;
import mil.nga.giat.geowave.datastore.hbase.util.ConnectionPool;

/**
 * Hello world!
 *
 */
public class HBaseQueryTests 
{
	private static final ThreadLocal<DateFormat> dateFormat = new ThreadLocal<DateFormat>() {
		@Override
		protected DateFormat initialValue() {
			return new SimpleDateFormat(
					"yyyy-MM-dd HH:mm:ss");
		}
	};

	public static Date parseDate(
			String source )
			throws ParseException {
		return dateFormat.get().parse(
				source);
	}
	
	private static HBaseDataStore dataStore;

	private static void setup() throws Exception{
		
		final String ZOOKEEPER = "shineassun:2181";
		final String NAMESPACE = "geowave.geolife-temporal";
		
		ConnectionPool connectionPool = ConnectionPool.getInstance();
		Connection connection = connectionPool.getConnection(ZOOKEEPER);
		dataStore = new HBaseDataStore(new BasicHBaseOperations(connection, NAMESPACE));
		
		
	}
	
	static public  void executePolygonAndTimeRangeQuery() throws Exception
	{
	
		Coordinate[] coordinates= new Coordinate[5];
		coordinates[0] = new Coordinate(-180, -90);
		coordinates[1] = new Coordinate(-180, 90);
		coordinates[2] = new Coordinate(180, 90);
		coordinates[3] = new Coordinate(180, -90);
		coordinates[4] = new Coordinate(-180, -90);
		
		final SpatialTemporalQuery query = new SpatialTemporalQuery(
				parseDate("2008-10-23 02:53:10"),
				parseDate("2008-10-23 02:53:55"),
						GeometryUtils.GEOMETRY_FACTORY.createPolygon(coordinates),
				CompareOperation.CONTAINS);

		System.out.println("Executing query, expecting to match three points...");

		final CloseableIterator<SimpleFeature> iterator = dataStore.query(
				new QueryOptions(),
				query);

		while (iterator.hasNext()) {
			System.out.println("Query match: " + iterator.next().getAttribute("Timestamp"));
		}
		
		System.out.println("=====================");
		
		iterator.close();

	}
	
    public static void main( String[] args ) throws Exception
    {
        System.out.println( "Hello World!" );
        
        setup();
        
        executePolygonAndTimeRangeQuery();
    }
}
