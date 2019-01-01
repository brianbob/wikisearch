<?php

namespace Drupal\wikisearch\Commands;

use Drush\Commands\DrushCommands;

/**
 * A Drush commandfile.
 *
 * In addition to this file, you need a drush.services.yml
 * in root of your module, and a composer.json file that provides the name
 * of the services file to use.
 */
class wikisearchCommands extends DrushCommands {
  /**
   * Echos back hello with the argument provided.
   *
   * @command wikisearch:wikiscrape
   * @aliases wikiscrape
   * @usage wikisearch:wikiscrape
   *   Scrape wikipedia
   */
  public function wikiscrape() {
    $wiki = new WikiSearch();
    $wiki->scrape;
  }

}
