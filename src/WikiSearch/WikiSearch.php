<?php

require_once drupal_get_path('MODULE', 'wikisearch') . '/includes/simple_html_dom.php';

use Drupal\wikisearch\LinksList\LinksList;

class WikiSearch {

  function __construct() {

  }

  public function scrape() {
    // Get our list of links to crawl and scrape.
    $list = new LinksList();
    $items = $list->get_links();
    // Iterate over the list.
    foreach ($items as $url) {
      $html = file_get_html($url->link);
      // Check to see if the page we get back has content.
      if ($html) {
        // Get all the links in the resulting page.
        foreach ($html->find('a') as $url) {
          // Check out the link and see if it's one we want to explore and
          // haven't already explored. If it is, get the clean and formatted
          // version for entry into the database.
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
}
