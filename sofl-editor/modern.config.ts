import { appTools, defineConfig } from '@modern-js/app-tools';

// https://modernjs.dev/en/configure/app/usage
export default defineConfig({
  runtime: {
    router: true,
  },
  source: {
    mainEntryName: 'index',
  },
  output: {
    distPath: {
      html: '',
    },
  },
  html: {
    disableHtmlFolder: true,
  },
  plugins: [
    appTools({
      bundler: 'experimental-rspack',
    }),
  ],
});
