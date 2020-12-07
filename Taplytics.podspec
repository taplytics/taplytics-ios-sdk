Pod::Spec.new do |s|
  s.name         = 'Taplytics'
  s.version      = '3.3.0'
  s.author       = { 'Taplytics' => 'help@taplytics.com' }
  s.license      = { :type => 'Commercial', :text => 'See https://taplytics.com/terms' }
  s.homepage     = 'https://taplytics.com'
  s.summary      = 'iOS framework for using the Taplytics native mobile A/B testing service.'
  s.description  = 'For installation instructions, please visit: https://github.com/taplytics/taplytics-ios-sdk'
  s.source = { :git => 'https://github.com/taplytics/taplytics-ios-sdk.git', :tag => "#{s.version}" }
  s.platform = :ios, '8.0'
  s.frameworks = 'CoreTelephony', 'SystemConfiguration', 'JavaScriptCore'
  s.preserve_paths = 'Taplytics.framework'
  s.source_files = s.public_header_files = "Taplytics.framework/**/*.h"
  s.vendored_frameworks = "Taplytics.framework"
  s.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
end
