<?php

use Drupal\Core\Database\Database;

  class LinksList {

    function __construct() {

    }

    function get_links($limit = NULL) {
      // Retrieves a \Drupal\Core\Database\Connection which is a PDO instance
      $connection = Database::getConnection();
      $query = $connection->select('wikisearch_to_search', 'wts')->fields('wts', array());

      // If a limit was passed, set it on the query.
      if (!is_null($connection) && is_numeric($limit)) {
        $query->range(0, $limit);
      }

      // Execute the statement
      $data = $query->execute();
      // Return all the results
      return $data->fetchAll(\PDO::FETCH_OBJ);
    }

    function add(Link $link) {
      if($link->url != NULL) {
        $connection = \Drupal\Core\Database\Database::getConnection();
        $db_name = $link->searched ? 'wikisearch_already_searched' : 'wikisearch_to_search';

        $fields = array(
          'link' => $link->url,
          'created' => $link->created,
          'changed' => $link->changed,
        );

        $connection->insert($db_name)
          ->fields($fields)
          ->execute();
      }
    }

    function remove($url) {
      // @TODO
    }
}
