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
class DBCArticleMigration extends BasicDBCMigration {
  public function __construct() {
    parent::__construct();

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'int',
          'not null' => TRUE,
          'alias' => 'news',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    // We have a more complicated query. The Migration class fundamentally
    // depends on taking a single source row and turning it into a single
    // Drupal object, so how do we deal with zero or more terms attached to
    // each node? One way (demonstrated for MySQL) is to pull them into a single
    // comma-separated list.
    $query = db_select(DBC_DATABASE . '.news', 'news')
             ->fields('news', array('id', 'headline', 'created', 'modified'));

    // Source
    $this->source = new MigrateSourceSQL($query);

    // Destination
    $this->destination = new MigrateDestinationNode('article');

    // Mapped fields
    $this->addFieldMapping('nid', 'id');
    $this->addFieldMapping('uid', NULL)->defaultValue(1);
    $this->addFieldMapping('title', 'headline');
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('changed', 'modified');
    $this->addFieldMapping('status', 'status');

    // $this->addUnmigratedSources(array());
    $this->addUnmigratedDestinations(array(
      'promote', 'sticky', 'revision', 'log', 'language', 'tnid', 'translate',
      'revision_uid', 'is_new',
    ));
  }

  public function prepareRow($row) {
    switch ($row->status) {
      case 'hidden':
        $row->status = 0;
        break;
      default:
        $row->status = 1;
        break;
    }
  }

  function country($name) {
    $country = array(
       1 => '_none',
       2 => 'DE',
       3 => 'US',
       4 => 'FR',
       5 => 'NL',
       6 => 'CH',
       7 => 'AU',
       8 => 'JP',
      10 => 'DK',
      11 => '_none', // Wales
      12 => 'BG',
      13 => 'FI',
      14 => 'CA',
      15 => 'BR',
      16 => 'EG',
      17 => 'RU',
      18 => 'CO',
      19 => 'BE',
      20 => 'AT',
      21 => 'IT',
      22 => 'IN',
      23 => 'ES',
      24 => 'NZ',
    );
    return $country[$name];
  }
}

class DBCArticleCollectionMigration extends BasicDBCMigration {
  public function __construct() {
    parent::__construct();

    $this->dependencies = array('DBCArticle');

    $query = db_select(DBC_DATABASE . '.news', 'n')
             ->fields('n');

    // Source
    $this->source = new MigrateSourceSQL($query, array()/*, $count_query*/);

    $this->destination = new MigrateDestinationFieldCollection(
      'field_content',
      array('host_entity_type' => 'node')
    );
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'int',
          'not null' => TRUE,
          'alias' => 'n',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $this->addFieldMapping('host_entity_id', 'article')->sourceMigration('DBCArticle');

    $this->addFieldMapping('field_subheadline', 'subhead1');
    $this->addFieldMapping('field_body', 'copy1');
  }
}
