<?php
/**
* @file Contains the code to generate the custom drush commands.
*/

require_once 'includes/simple_html_dom.php';


/**
* Implements hook_drush_command().
*/
function wikisearch_drush_command() {
 $items = array();
 $items['scrape'] = [
   'description' => 'Scrape wikipedia for links and content',
   'aliases' => ['wikiscrape'],
 ];
 return $items;
}

/**
*
*/
function drush_wikisearch_scrape($name = '') {
  // Get our list of links to crawl and scrape.
  //$links = wikisearch_get_links();
  $list = new LinksList();
  $items = $list->get_links();
  // Iterate over the list.
  foreach ($items as $url) {
    $html = file_get_html($url->link);
    // Check to see if the page we get back has content.
    if ($html) {
      // Get all the links in the resulting page.
      foreach ($html->find('a') as $url) {
        // Check out the link and see if it's one we want to explore and haven't already explored.
        // If it is, get the clean and formatted version for entry into the database.
        $link = new Link($url->href);
        // Clean the url a bit before inserting it into the database.
        $link->clean();
        // Validate the link.
        $link->validate();
        //$link->parse();
        //$link->print_url(); // TESTING
        // Add the new link to our list.
        $list->add($link);
      }
      // Now that we've iterated over all the links in this page, remove it.
      $list->remove($url->link);
    }
  }
}

/**
 * [wikisearch_get_links description]
 * @param  [type] $number [description]
 * @return [type]         [description]
 *
 * Adapted from: https://api.drupal.org/api/drupal/core%21lib%21Drupal%21Core%21Database%21Connection.php/function/Connection%3A%3Aselect/8.2.x#comment-60780
 */
function wikisearch_get_links($limit = NULL) {
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


