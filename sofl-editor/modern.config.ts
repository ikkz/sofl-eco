import { appTools, defineConfig } from '@modern-js/app-tools';
import { tailwindcssPlugin } from '@modern-js/plugin-tailwindcss';

import ArcoWebpackPlugin from '@arco-plugins/webpack-react';

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
    new ArcoWebpackPlugin(),
    tailwindcssPlugin(),
  ],
});
