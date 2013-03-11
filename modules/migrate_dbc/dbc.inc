<?php

define('DBC_DATABASE', 'dbc');

/**
 * @file
 */
abstract class BasicDBCMigration extends DynamicMigration {
  public function __construct() {
    parent::__construct();

    $this->team = array(
      new MigrateTeamMember('Stefan Auditor', 'stefan.auditor@erdfisch.de', t('Implementor')),
    );

    // Individual mappings in a migration can be linked to a ticket or issue
    // in an external tracking system. Define the URL pattern here in the shared
    // class with ':id:' representing the position of the issue number, then add
    // ->issueNumber(1234) to a mapping.
    $this->issuePattern = 'https://github.com/sanduhrs/dbc/issues/:id:';
  }
}

/** 
 *
 */
class ArticleMigration extends BasicDBCMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Beers of the world');

    // You may optionally declare dependencies for your migration - other migrations
    // which should run first. In this case, terms assigned to our nodes and
    // the authors of the nodes should be migrated before the nodes themselves.
    $this->dependencies = array('BeerTerm', 'BeerUser');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'bid' => array(
          'type' => 'int',
          'not null' => TRUE,
          'description' => 'Beer ID.',
          'alias' => 'b',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    // We have a more complicated query. The Migration class fundamentally
    // depends on taking a single source row and turning it into a single
    // Drupal object, so how do we deal with zero or more terms attached to
    // each node? One way (demonstrated for MySQL) is to pull them into a single
    // comma-separated list.
    $query = db_select('migrate_example_beer_node', 'b')
             ->fields('b', array('bid', 'name', 'body', 'excerpt', 'aid', 'countries',
              'image', 'image_alt', 'image_title', 'image_description'));
    $query->leftJoin('migrate_example_beer_topic_node', 'tb', 'b.bid = tb.bid');
    // Gives a single comma-separated list of related terms
    $query->groupBy('tb.bid');
    $query->addExpression('GROUP_CONCAT(tb.style)', 'terms');

    // By default, MigrateSourceSQL derives a count query from the main query -
    // but we can override it if we know a simpler way
    // $count_query = db_select('migrate_example_beer_node', 'b');
    // $count_query->addExpression('COUNT(bid)', 'cnt');

    // Source
    $this->source = new MigrateSourceSQL($query, array()/*, $count_query*/);

    // Destination
    $this->destination = new MigrateDestinationNode('migrate_example_beer');

    // Mapped fields
    $this->addFieldMapping('title', 'name');
  }
}
