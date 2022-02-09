Pod::Spec.new do |s|
  s.name         = 'Taplytics'
  s.version      = '4.0.0'
  s.author       = { 'Taplytics' => 'help@taplytics.com' }
  s.license      = { :type => 'Commercial', :text => 'See https://taplytics.com/terms' }
  s.homepage     = 'https://taplytics.com'
  s.summary      = 'iOS framework for using the Taplytics native mobile A/B testing service.'
  s.description  = 'For installation instructions, please visit: https://github.com/taplytics/taplytics-ios-sdk'
  s.source = { :git => 'https://github.com/taplytics/taplytics-ios-sdk.git', :tag => "#{s.version}" }
  s.platform = :ios, '10.0'
  s.frameworks = 'CoreTelephony', 'SystemConfiguration', 'JavaScriptCore'
  s.vendored_frameworks = 'Taplytics.xcframework'
end
