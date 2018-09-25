<?php
/**
* @file Contains the code to generate the custom drush commands.
*/

/**
 * Implements hook_drush_command().
 */
function wikisearch_drush_command() {
 $items = [];
 $items['scrape'] = [
   'description' => 'Scrape links for links and content',
   'aliases' => ['wikiscrape'],
   'drupal dependencies' => ['wikisearch'],
 ];

 return $items;
}

/**
 *
 */
function drush_wikisearch_scrape() {
  wikisearch_scrape();
}



