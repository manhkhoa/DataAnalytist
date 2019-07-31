<?php

/**
 * @file
 * Bartik's theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template normally located in the
 * modules/system directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 * - $hide_site_name: TRUE if the site name has been toggled off on the theme
 *   settings page. If hidden, the "element-invisible" class is added to make
 *   the site name visually hidden, but still accessible.
 * - $hide_site_slogan: TRUE if the site slogan has been toggled off on the
 *   theme settings page. If hidden, the "element-invisible" class is added to
 *   make the site slogan visually hidden, but still accessible.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['header']: Items for the header region.
 * - $page['featured']: Items for the featured region.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['triptych_first']: Items for the first triptych.
 * - $page['triptych_middle']: Items for the middle triptych.
 * - $page['triptych_last']: Items for the last triptych.
 * - $page['footer_firstcolumn']: Items for the first footer column.
 * - $page['footer_secondcolumn']: Items for the second footer column.
 * - $page['footer_thirdcolumn']: Items for the third footer column.
 * - $page['footer_fourthcolumn']: Items for the fourth footer column.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see bartik_process_page()
 * @see html.tpl.php
 */

global $base_url, $user;
$user = user_load($user->uid);

$path = drupal_get_path('theme', 'os_admin').'/inc/notification.json';

if(file_exists($path)){
  $file_content = file_get_contents($path);
  $data = json_decode($file_content, true);
} 

$total_new_event = $data[0]['total_new_event'];
$total_new_drug = $data[0]['total_new_drug'];
$total_recall = $data[0]['total_recall'];

$inc_ae = $data[0]['inc_ae'];
$inc_ae_year = $data[0]['inc_ae_year'];
$highest_drug_name = $data[0]['highest_drug_name'];
$highest_drug_percent = $data[0]['highest_drug_percent'];

$highest_drug_name_q = $data[0]['highest_drug_name_q'];
$highest_drug_percent_q = $data[0]['highest_drug_percent_q'];

$company_name_q = $data[0]['company_name_q'];
$company_name_y = $data[0]['company_name_y'];

$last_quarter_vl = $data[0]['last_quarter_vl'];
$last_year_vl = $data[0]['last_year_vl'];


$get_user_online_list = get_user_online_list();

function get_user_online_list(){
  // Count users active within the defined period.
  $interval = REQUEST_TIME - variable_get('user_block_seconds_online', 900);

  // Perform database queries to gather online user lists. We use s.timestamp
  // rather than u.access because it is much faster.
  $authenticated_count = db_query("SELECT COUNT(DISTINCT s.uid) FROM {sessions} s WHERE s.timestamp >= :timestamp AND s.uid > 0", array(':timestamp' => $interval))->fetchField();

  $output = '';

  // Display a list of currently online users.
  $max_users = variable_get('user_block_max_list_count', 10);
  $items = array();
  if ($authenticated_count && $max_users) {
    $items = db_query_range('SELECT u.uid, u.name, MAX(s.timestamp) AS max_timestamp FROM {users} u INNER JOIN {sessions} s ON u.uid = s.uid WHERE s.timestamp >= :interval AND s.uid > 0 GROUP BY u.uid, u.name ORDER BY max_timestamp DESC', 0, $max_users, array(':interval' => $interval))->fetchAll();  
  }

  return $items;

}

// path to user profile
$url = $user->picture->uri;
$url = parse_url($url);
$path = $url['path'];



?>

<div id="layout-container"> 
  <!--Left navbar start-->
  <div id="nav"> 
    <!--logo start-->
    <div class="profile">
      <div class="logo">
        <?php if ($logo): ?>
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
            <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
          </a>
        <?php endif; ?>
      </div>
    </div>
    <!--logo end--> 
    
    <!--navigation start-->
    <ul class="navigation">
      <li> <a title="Home" class="dasboard active" href="<?php print $base_url; ?>"><i class="fa fa-home"></i><span>Dashboard</span></a></li>

      <?php if($user->roles[3]){ ?>
        <li> <a title="Pending Registrations" class="pending-registration" href="<?php print($base_url.'/pending-registration'); ?>"><i class="fa fa-table"></i><span>Registrations</span></a></li>
      <?php } ?>

      <?php if($user->roles[3] || $user->roles[4]){ ?>
        <li> <a title="Adverse Events Chart" class="circle-company" href="<?php print($base_url.'/adverse-events-chart'); ?>"><i class="fa fa-list-alt"></i><span>Adverse Events</span></a></li>
        <li> <a title="Drugs Chart" class="circle-drugs" href="<?php print($base_url.'/drugs-chart'); ?>"><i class="fa fa-compass"></i><span>Drugs</span></a></li>
        <li> <a title="Recalls Chart" class="recall-chart" href="<?php print($base_url.'/recalls-chart'); ?>"><i class="fa fa-bar-chart-o"></i><span>Recalls</span></a></li>
      <?php } ?>


      <?php if($user->roles[1]){ ?>
        <li> <a title="Register" class="register" href="<?php print($base_url.'/register'); ?>"><i class="fa fa-list-alt"></i><span>Register</span></a></li>
         <li> <a title="Login" class="login" href="<?php print($base_url.'/user/login'); ?>"><i class="fa fa-table"></i><span>Login</span></a></li>
      <?php } ?>


          
    </ul>
    <!--navigation end--> 
  </div>
  <!--Left navbar end--> 
  
  <!--main start-->
  <div id="main">
    <div class="head-title">
      <div class="menu-switch"><i class="fa fa-bars"></i></div>
      <!--row start-->
      <div class="row horizontal-row"> 
        <!--col-md-12 start-->
        <div class="col-md-12"> 
          <!--profile dropdown start-->
          <?php if ($user->uid != 0): ?>

          <ul class="user-online pull-right">
           <li class="dropdown"> <a href="#" class="dropdown-toggle rightbar-switch" data-toggle="dropdown"> <i class="fa fa-bars"></i></a>
              <ul class="dropdown-menu extended tasks-bar">
                <div class="notify-arrow notify-arrow-red"></div>
                <li>
                  <p class="red"><?php print(count($get_user_online_list)); ?> users online</p>
                </li>      

                <li class="user-name-list">
                  <?php 
                    foreach ($get_user_online_list as $key => $value) {
                      print('<div class="user-name"><i class="fa fa-circle-o"></i> <a href="#">'.$value->name.'</a></div>');
                    } 
                  ?>
                </li>

              </ul>
            </li><!--task end--> 
          </ul>


          <ul class="user-info pull-right fadeInLeftBig animated">
           
            <li class="profile-info dropdown"> 
              <a data-toggle="dropdown" class="dropdown-toggle" href="#"> 
               <img class="img-circle" width="50" height="50" alt="" src="<?php print($base_url.'/sites/default/files/pictures'.$path); ?>">
            
              <?php print($user->name); ?></a>
              <ul class="dropdown-menu">
                <li class="caret"></li>
                <li> <a href="<?php print($base_url."/user/".$user->uid."/edit"); ?>"> <i class="fa fa-user"></i> Edit Profile </a> </li>
                <li> <a href="<?php print($base_url."/user/logout") ?>"> <i class="fa fa-clipboard"></i> Log Out </a> </li>
              </ul>
            </li>

            <!-- <li class="hidden-xs"><a class="toggle-menu menu-right push-body jPushMenuBtn rightbar-switch" href="javascript:;"><i class="fa fa-bars"></i></a></li>
 -->
            
            
          </ul><!--profile dropdown end--> 
          

          <?php endif; ?>


          <!-- Notification -->

            <!--top nav start-->
          <ul class="nav top-menu hidden-xs notify-row fadeInRightBig animated">
            <!--task start-->
            <li class="dropdown"> <a href="#" class="dropdown-toggle" data-toggle="dropdown"> <i class="fa fa-tasks"></i> <span class="badge bg-success"><?php print($total_new_event); ?></span> </a>
              <ul class="dropdown-menu extended tasks-bar">
                <div class="notify-arrow notify-arrow-red"></div>
                <li>
                  <p class="red">You have <?php print($total_new_event); ?> new adverse events.</p>
                </li>                
              </ul>
            </li><!--task end--> 
            
            <!--message start-->
            <li class="dropdown" id="header_inbox_bar"> <a href="#" class="dropdown-toggle" data-toggle="dropdown"> <i class="fa fa-envelope-o"></i> <span class="badge bg-important"><?php print($total_new_drug); ?></span> </a>
              <ul class="dropdown-menu extended tasks-bar">
                <div class="notify-arrow notify-arrow-red"></div>
                <li>
                  <p class="red">You have <?php print($total_new_drug); ?> new drugs.</p>
                </li>                
              </ul>
            </li><!--message end--> 
            
            <!--notification start-->
            <li class="dropdown" id="header_notification_bar"> <a href="#" class="dropdown-toggle" data-toggle="dropdown"> <i class="fa fa-bell-o"></i> <span class="badge bg-warning"><?php print($total_recall); ?></span> </a>
              <ul class="dropdown-menu extended tasks-bar">
                <div class="notify-arrow notify-arrow-red"></div>
                <li>
                  <p class="red">You have <?php print($total_recall); ?> new recallings.</p>
                </li>                
              </ul>
            </li><!--notification end-->
          </ul><!--top nav end--> 
          <!-- End Notification -->
        
        </div>
        <!--col-md-12 end--> 

      </div>
      <!--row end--> 
    </div>
    <!--margin-container start-->
    <div class="margin-container"> 
      <!--scrollable wrapper start-->
      <div class="scrollable wrapper"> 
        <!--row start-->
        <div class="row"> 

          <!--col-md-12 start-->
          <div class="col-md-12 front-block">
            <div class="page-heading front-title">
              <h1>Dashboard</h1>
            </div>
          </div>

          <!--col-md-12 start-->
          <div class="col-md-12 not-front-block">
            <div class="page-heading">
              <h1 class="title" id="page-title">
                <?php print $title; ?>
              </h1>
            </div>

            <?php if ($messages): ?>
              <div id="messages"><div class="section clearfix">
                <?php print $messages; ?>
              </div></div> <!-- /.section, /#messages -->
            <?php endif; ?>
          </div> <!-- End of col 12 -->

          <div class="col-sm-6 col-md-3 front-block first">
            <div class="box-info">
              <div class="title-box">
                <h3>Increase in Adverse Events</h3>
                <div class="blue-bg">
                  <p class="number-event-title">Last Quarter</p>
                  <h1 class="company-name number-drug"><?php print $inc_ae; ?>%</h1>
                  <p class="number-event"><?php print ('('.$last_quarter_vl.' events)'); ?></p>
                </div>
                <i class="fa fa-tablet"></i>
                <div id="work-progress1" class="pull-right"></div>
              </div>
            </div>
          </div>
          <div class="col-sm-6 col-md-3 front-block second">
            <div class="box-info">
              <div class="title-box">
                <h3>Increase in Adverse Events</h3>
                <div class="red-bg">
                  <p class="number-event-title">Last Year</p>
                  <h1 class="company-name number-drug"><?php print $inc_ae_year; ?>%</h1>
                  <p class="number-event"><?php print ('('.$last_year_vl.' events)'); ?></p>
                </div>
                <i class="fa fa-medkit"></i>
                <div id="work-progress2" class="pull-right"></div>
              </div>
            </div>
          </div>
          <div class="col-sm-6 col-md-3 front-block third">
            <div class="box-info">
              <div class="title-box">
                <h3>Drug with Most Adverse Reactions</h3>
                <div class="green-bg">
                  <p class="number-event-title drug">Last Quarter</p>
                  <p class="company-name number-drug drug-name"><?php print ($highest_drug_name_q.' ('.$highest_drug_percent_q.' events)'); ?></p>
                  <p class="company-name number-drug"><?php print ('Manufacturer: '.$company_name_q); ?></p>
                  
                </div>
                <i class="fa fa-volume-up"></i>
                <div id="work-progress3" class="pull-right"></div>
              </div>
            </div>
          </div>
          <div class="col-sm-6 col-md-3 front-block last">
            <div class="box-info">
              <div class="title-box">                
                <h3>Drug with Most Adverse Reactions</h3>
                <div class="maroon-bg">
                  <p class="number-event-title drug">Till Date</p>
                  <p class="company-name number-drug drug-name"><?php print ($highest_drug_name.' ('.$highest_drug_percent.' events)'); ?></p>
                  <p class="company-name number-drug"><?php print ('Manufacturer: '.$company_name_y); ?></p>
                  
                </div>
                <i class="fa fa-comment-o"></i>
                <div id="work-progress4" class="pull-right"></div>
              </div>
            </div>
          </div>

        </div>
        <!--row end-->
        <div class="row">

            <div id="page-wrapper"><div id="page">
                <div id="content" class="column"><div class="section"> 
                  <?php print render($page['content']); ?>   
                </div></div> <!-- /.section, /#content -->  
            </div></div> <!-- /#page, /#page-wrapper -->


          
      
        </div>
        <!--row end-->
    
        
      </div>
      <!--scrollable wrapper end--> 
    </div>
    <!--margin-container end--> 
  </div>
  <!--main end-->

  <!-- sidebar chats -->
  <nav class="atm-spmenu atm-spmenu-vertical atm-spmenu-right side-chat">
    <div href="#" class="sub-header">
      <div class="icon"><i class="fa fa-user"></i></div> <p>Online (<?php print(count($get_user_online_list)); ?>)</p>
    </div>
    <div class="content">
      <ul class="nav nav-pills nav-stacked contacts">
        <?php 
          foreach ($get_user_online_list as $key => $value) {
            print('<li class="online"><a href="#"><i class="fa fa-circle-o"></i>'.$value->name.'</a></li>');
          }        

        ?>
       
      </ul>  
    </div>    
  </nav>
  <!-- /sidebar chats -->   
   
</div>

<!-- End -->


