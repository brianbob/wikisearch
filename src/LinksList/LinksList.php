<?php

use Drupal\Core\Database\Database;
use Drupal\wikisearch\Link\Link;

class LinksList {

  function __construct() {

  }

  /**
   * Returns a list of links to search.
   *
   * @param  int $limit
   *    The number of links to
   * @return object
   *   The datbase results object.
   */
  function get_links($limit = NULL) {
    // Retrieves a \Drupal\Core\Database\Connection which is a PDO instance
    $connection = Database::getConnection();
    $query = $connection->select('wikisearch_to_search', 'wts')
      ->fields('wts', array());

    // If a limit was passed, set it on the query.
    if (isset($limit) && is_numeric($limit)) {
      $query->range(0, $limit);
    }

    // Execute the statement
    $data = $query->execute();
    // Return all the results
    return $data->fetchAll(\PDO::FETCH_OBJ);
  }

  /**
   * Adds a link to the 'to search' list.
   *
   * @param Link $link
   *   The link to add to the list
   */
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

  /**
   * Remove a link from the 'to search' list.
   *
   * @param  String $url
   *   The URL to remove
   */
  function remove($url) {
    if($url != NULL) {
      $connection = \Drupal\Core\Database\Database::getConnection();
      $db_name = $link->searched ? 'wikisearch_already_searched' : 'wikisearch_to_search';

      $insert_fields = array(
        'link' => $url,
        'created' => REQUEST_TIME,
        'changed' => REQUEST_TIME,
      );

      // Add the url to the 'already searched' table
      $connection->insert('wikisearch_already_searched')
        ->fields($insert_fields)
        ->execute();

      // Remove the link from the 'to search' table
      $connection->delete('wikisearch_to_search')
        ->fields(array('link' => $url))
        ->execute();
    }
  }
}
