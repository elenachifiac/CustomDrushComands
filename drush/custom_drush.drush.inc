<?php

//use Drupal\html_dom_scraper\Helper\SqlQuery;
//use Drupal\html_dom_scraper\Helper\simple_html_dom;
//use Drupal\html_dom_scraper\Helper\HtmlDomScraperHelper;
//Use Drupal\node\Entity\Node;

/**
 * Implements hook_drush_command().
 */
function custom_drush_drush_command() {
  $items = array();
  $items['testing-demo'] = [
    'description' => 'List all migrations with current status.',
    'aliases' => ['testing-demo'],
  ];
  $items['prompt-demo'] = [
    'description' => 'List all migrations with current status.',
    'aliases' => ['prompt-demo'],
  ];
  $items['functions-demo'] = [
    'callback' => 'functions_drush_custom_list',
    'description' => 'List all migrations with current status.',
    'aliases' => ['functions-demo'],
  ];
  $items['limit-demo'] = [
    'callback' => 'provide_limit_function',
    'description' => 'List all migrations with current status.',
    'aliases' => ['limit-demo'],
  ];
  $items['choice-demo'] = [
    'callback' => 'choice_prompt',
    'description' => 'List all migrations with current status.',
    'aliases' => ['choice-demo'],
  ];
  $items['batch-demo'] = [
    'callback' => 'drush_batch_demo',
    'description' => 'List all migrations with current status.',
    'aliases' => ['batch-demo'],
  ];
  $items['custom-argument'] = array(
    'callback' => 'my_callback_drush_custom_drush_testing_demo',
    'description' => dt(''),
    'options' => array(
      'arg_1' => array(
        'description' => 'First Arg.',
      ),
      'arg_2' => array(
        'description' => 'Second Arg.',
      ),
      'arg_3' => array(
        'description' => 'Third Arg.',
      ),
    ),
    'examples' => array(
      'drush custom-argument --arg_1=Alok --arg_2=Singh --arg_3=Narwaria' => '',
    ),
  );
  $items['node-count-demo'] = array(
    'callback' => 'custom_node_count_demo',  // Callback function
    'description' => 'Drush command to get node count of particular node type.',
    'aliases' => array('ncd'), // alias of command
    'examples' => array(      // List these example when user types : drush help nc
      'Get all nodes count' => 'drush ncd',
      'Get articles node count' => 'drush ncd article',
      'Get articles, pages node count' => 'drush ncd article page',
    ),
  );
  $items['table-demo'] = array(
    'callback' => 'custom_drush_table',  // Callback function
    'description' => 'Table demo',
    'examples' => array(      // List these example when user types : drush help nc
      'Get all nodes count' => 'drush table-demo',
      'Get articles node count' => 'drush table-demo article',
      'Get articles, pages node count' => 'drush table-demo article page',
    ),
  );
  return $items;
}

/**
 * Call back function drush_custom_drush_command_say_hello()
 * The call back function name in the  following format
 *  drush_{module_name}_{item_id_for_command}()
 */
function drush_custom_drush_testing_demo() {
  drush_print('Welcome to Drush Interface');
}

/**
 * Call back function drush_custom_drush_command_say_hello()
 * The call back function name in the  following format
 *   drush_{module_name}_{item_id_for_command}()
 */
function drush_custom_drush_prompt_demo() {
  $name = drush_prompt("Enter the name", '', TRUE);
  drush_print(dt('Welcome @name', ['@name' => $name]));
}

/**
 * Call back function my_callback_drush_custom_drush_testing_demo()
 * The call back function name in the  following format
 *   drush_{module_name}_{item_id_for_command}()
 */
function my_callback_drush_custom_drush_testing_demo() {
  $arg1 = drush_get_option('arg_1');
  $arg2 = drush_get_option('arg_2');
  $arg3 = drush_get_option('arg_3');
  if (!$arg1) {
    $arg1 = drush_prompt("Enter the First name", NULL, TRUE);
  }
  if (!$arg2) {
    $arg1 = drush_prompt("Enter the Middle name", NULL, TRUE);
  }
  if (!$arg3) {
    $arg3 = drush_prompt("Enter the Last name", NULL, TRUE);
  }
  $tokens = array('@opt1' => $arg1, '@opt2' => $arg2, '@opt3' => $arg3);
  drush_print(dt('First Name : @opt1, Middle Name: @opt2, Last Name: @opt3', $tokens));
}

/**
 * Call back function my_callback_drush_custom_drush_testing_demo()
 * The call back function name in the  following format
 *   drush_{module_name}_{item_id_for_command}()
 */
function functions_drush_custom_list() {
  drush_log(dt('Custom drush log function :)'), 'success');
  drush_log(dt('Custom drush log function :)'), 'warning');
  drush_log(dt('Custom drush log function ;)'), 'error');
  //return drush_set_error(dt('Custom drush set error function :)'));
  return drush_set_error('custom_drush', dt('Destination directory !destination is not writable.', array('!destination' => $destination)));
}

function provide_limit_function() {
  list($start, $end) = limitPrompt();
  if ($start == 0 && $end == 0) {
    drush_log(dt('Bhai kuch to limit pass kardo :)'), 'error');
  }
  else {
    drush_log(dt('Drush Sttart @start , End @end limits. :)', ['@start' => $start, '@end' => $end]), 'success');
  }
}

/**
 * Call back function.
 * The call back function name in the  following format
 *
 * @return type array.
 */
function choice_prompt() {
  $choiceList = [1 => 'Bear', 2 => 'Vodka', 3 => 'Wine', 4 => 'chicken', 5 => 'All of above :)'];
  $choice = drush_choice($choiceList, dt("Choose the option from migration interface."));
  switch ($choice) {
    case 0:
      drush_log(dt('Bhai kuch to le lo :)'), 'warning');
      break;
    case 5:
      drush_log(dt('Bhai barat me aaya hai kya :)'), 'error');
      break;
    default :
      drush_log(dt('I love @choice:)', ['@choice' => $choiceList[$choice]]), 'success');
  }
}

/**
 * Call back function.
 * The call back function name in the  following format
 *
 * @return type array.
 */
function limitPrompt() {
  $islimit = drush_prompt("Do you want to provide limit", 'yes', true);
  $start = 0;
  $end = 0;
  if ($islimit == 'yes') {
    $start = drush_prompt("Start ", 0, FALSE);
    $end = drush_prompt("End", 100, FALSE);
  }
  return [$start, $end];
}

/**
 * Call back function drush_custom_drush_command_say_hello()
 * The call back function name in the  following format
 *   drush_{module_name}_{item_id_for_command}()
 */
function drush_batch_demo() {
  drush_print('Welcome to drush interface');
  list($start, $end) = limitPrompt();
  if ($start == $end || $start >= $end) {
    drush_log(t('Bhai ungali mat kar :)'), 'error');
  }
  else {
    $batch = CustomBatch($start, $end);
    if ($batch !== NULL) {
      // Initialize the batch.
      batch_set($batch);
      // Start the batch process.
      drush_backend_batch_process();
    }
    else {
      drush_log(t('No records found :)'), 'success');
    }
  }
}

function CustomBatch($start = null, $end = null) {
  return array(
    'operations' => array(
      array('my_custom_batch_example', array($start, $end))
    ),
    'finished' => 'my_custom_batch_example_finished',
    'title' => t('My Custom Batch Example'),
    'init_message' => t('Updation is starting.'),
    'progress_message' => t('Updating...'),
    'error_message' => t('Updation has encountered an error.'),
  );
}

function my_custom_batch_example_finished() {
  drush_log(t('Batch Run Successfully :)'), 'success');
}

function my_custom_batch_example($start = array(), $end = NULL, &$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = $start;
    $context['sandbox']['max'] = $end;
    $context['sandbox']['items_count'] = 1;
    $context['results']['result_count'] = $context['sandbox']['max'];
    drush_print_r("Batch started for item count is {$context['sandbox']['max']}");
  }
  if ($context['sandbox']['progress'] <= $context['sandbox']['max']) {
    $context['sandbox']['current_id'] = $context['sandbox']['progress'];
    drush_log(t('Count :count ', [':count' => $context['sandbox']['progress']]), 'success');
    $context['sandbox']['progress'] = $context['sandbox']['progress'] + $context['sandbox']['items_count'];
  }
  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}


/*
 * Callback function for hook_drush_command().
 */
function custom_node_count_demo() {
  // Get arguments passed in command, Ex: drush ncd page blog
  $args = func_get_args();
  if ($args) {
    // Loop for types
    foreach($args as $type){
      // Query to get count of particular type
       $result = \Drupal::database()->select('node', 'n')
      ->fields('n', array('nid'))
      ->countQuery()
      ->execute()
      ->fetchObject();
    $num_of_results = $result->expression;
      drush_print($type. "'s node count : " . $num_of_results);
    }

  }
  // If no type passed then return total count
  else {
    drush_print('No node types mentioned');
    
    $result = \Drupal::database()->select('node', 'n')
      ->fields('n', array('nid'))
      ->countQuery()
      ->execute()
      ->fetchObject();
    $num_of_results = $result->expression;
    drush_print('Count of all nodes : '. $num_of_results);
  }
}


/*
 * Callback function for hook_drush_command().
 */

function custom_drush_table() {
    $row = [['Heading 1','Heading 2'],['data 1','data 2']];
  drush_print_table($row,true,[50,30]);
}
